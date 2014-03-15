/**
 *************************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                            *
 *   AQUANODE: PROTOTIPAÇÃO DE UM NÓ SENSOR PARA REDES DE SENSORES AQUÁTICAS         *
 *************************************************************************************
 *                              BIBLIOTECA DE COMUNICAÇÃO I2C                        *
 *************************************************************************************
 * DESENVOLVIDO POR:LABORATÓRIO DE ENGENHARIA DE SISTEMA DE COMPUTAÇÃO UFV-FLORESTAL *
 * DATA:                                                                             *
 * APROVADO POR:                                                                     *
 * DATA:                                                                             *
 * VERSÃO:                                                                           *
 *************************************************************************************/

/**
 * @file I2C_Master.c
 * @brief A biblioteca I2C_MASTER tem o objetivo de possibilitar uma comunicacao via
 * I2C
 */

#include "i2cmaster.h"

/**@var unsigned char *pointer_rx_data
 * @brief Ponteiro para armazenar
 * os dados recebidos
 */
unsigned char  *pointer_rx_data;

/**@var unsigned char *pointer_tx_data
 * @brief Ponteiro para dados a serem enviados
 */
unsigned char *pointer_tx_data;

/**@var int tx_byte_ctr
 * @brief Contador de bytes a serem enviados
 */
int tx_byte_ctr;

/** @var int rx_byte_ctr
 *  @brief Contador de bytes a serem recebidos
 */
int rx_byte_ctr;

/**
 * @fn void I2C_init(unsigned char own_address)
 * @brief Inicializa comunicação I2C com dispositivo escravo
 * @param unsigned char own_address - Variavel referente ao endereco do dispositivo
 * @return Esta funcao nao possui retorno
 */
void I2C_init(unsigned char own_address){

  I2C_PORT_SEL |= SDA_PIN + SCL_PIN;
  P1SEL2|= BIT6 + BIT7; // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;
  UCB0CTL1 = UCSSEL_2 + UCTR + UCSWRST;
  UCB0BR0 = SCL_CLOCK_DIV;
  UCB0BR1 = 0;
  UCB0I2COA = own_address;
  UCB0CTL1 &= ~UCSWRST;
  if (UCB0STAT & UCBBUSY){
     I2C_PORT_SEL &= ~SCL_PIN;
     I2C_PORT_OUT &= ~SCL_PIN;
     I2C_PORT_DIR |= SCL_PIN;
     I2C_PORT_SEL |= SDA_PIN + SCL_PIN;
  }
  IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);
  IE2 &= ~(UCB0TXIE + UCB0RXIE);//desabilita as interrupções de envio e transmissão
}
/**@fn void I2C_send_data(unsigned char slave_address,unsigned char* tx_data,int num_bytes,unsigned char send_stop)
* @brief Envia dados para dispositivo escravo  desejado
* @param unsigned char slave_address - Varialvel referente ao endereço do dispositivo receptor da 
* msg a ser enviada.
* @param unsigned char* tx_data - Ponteiro referente aos dados a serem enviados
* @param int num_bytes - Variavel referente a quantidade de bytes a serem enviados
* @return Esta funcao nao possui retorno
*/
void I2C_send_data(unsigned char slave_address,unsigned char* tx_data,unsigned int num_bytes,unsigned char send_stop){
 
  while (UCB0STAT & UCBUSY);//verifica se i2c esta em uso
  pointer_tx_data = (unsigned char*)tx_data;//Aponta para dados a serem enviados
  tx_byte_ctr = num_bytes;//Numero de bytes a serem enviados
  UCB0CTL1 |= UCSWRST;//desabilita o modulo USCB
  UCB0I2CSA  = slave_address;//atualiza o endereço do dispositivo escravo 
  UCB0CTL1 |= UCTR;//i2c modo transmissor
  UCB0CTL1 &= ~UCSWRST;//habilita o modulo apos as configurações  
  IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);//limpa flag de interrupção de envio e recebimento
  IE2 &= ~(UCB0TXIE + UCB0RXIE);//desabilita as interrupções de envio e transmissão
  IE2 |= UCB0TXIE;//habilita interrupção de transmissão
  UCB0CTL1 |= UCTXSTT;//envia condição de start 
  __bis_SR_register(LPM0_bits + GIE);//coloca o cpu em baixo consumo e habilita interrupções gerais
  if(send_stop == 1){//verifica se a comunicação deve ser encerrada
    UCB0CTL1 |= UCTXSTP;//envia um stop para encerrar comunicação
    while(UCB0CTL1 & UCTXSTP);//verifica se o stop foi recebido
  }
}

/**
* @fn void I2C_receive_data(unsigned char slave_address,unsigned char* rx_data,int num_bytes)
* @brief Recebe dados do dispositivo escravo desejado
* @param unsigned char slave_address - Variavel referente ao endereço do dispositivo emissor
* da msg a ser recebida.
* @param unsigned char* rx_data - Variavel referente aos dados a serem recebidos
* @param int num_bytes - Variavel referente a quantidade de bytes a serem recebidos
* @return Esta funcao nao possui retorno
*/
void I2C_receive_data(unsigned char slave_address,unsigned char* rx_data,unsigned int num_bytes){

  pointer_rx_data = (unsigned char*)rx_data;//aponta para vetor de armazenamento
  rx_byte_ctr = num_bytes;//Numero de bytes a serem recebidos
  UCB0I2CSA  = slave_address;//atualiza o endereço do dispositivo escravo 
  UCB0CTL1 &= ~UCTR;//i2c modo receptor
  IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);//limpa flag de interrupção de envio e recebimento
  IE2 &= ~(UCB0TXIE + UCB0RXIE);//desabilita as interrupções de envio e transmissão
  IE2 |= UCB0RXIE;//habilita interrupção de recebimento
  UCB0CTL1 |= UCTXSTT;//envia condição de start 
  __bis_SR_register(LPM0_bits + GIE);//coloca o cpu em baixo consumo e habilita interrupções gerais
  UCB0CTL1 |= UCTXSTP;//envia um stop para encerrar comunicação
  while(UCB0CTL1 & UCTXSTP);//verifica se o stop foi recebido

}

/**
* @fn int I2C_tx_handler(void)
* @brief Trata a interrupcao de envio de mensagem
* @return Retorna um valor int (0 ou 1)
*/
short I2C_tx_handler(void){

    tx_byte_ctr--;
    UCB0TXBUF = *pointer_tx_data++;
    if(tx_byte_ctr <= 0){
      while(!(IFG2 & UCB0TXIFG));
      IE2 &=   ~UCB0TXIE;
      IFG2 &= ~UCB0TXIFG;
      return 1;
    }
    return 0;
}
/**
* @fn int I2C_rx_handler(void)
* @brief Trata a interrupcao de recebimento de mensagem
* @return Retorna um valor int (0 ou 1)
*/
short I2C_rx_handler(void){

     rx_byte_ctr--;
     *pointer_rx_data++ = UCB0RXBUF;
     if(rx_byte_ctr <= 0){
       while(!(IFG2 & UCB0RXIFG));
       IE2 &= ~UCB0RXIE;
       IFG2 &= ~UCB0RXIFG;
       return 1;
    }
    return 0;

}
/**
 * @fn void I2C_AckPolling()
 * @brief Verifica se I2C esta ocupada em modo de escrita
 * @return esta funcao nao possui retorno
 */
void I2C_ack_polling(){

   while (UCB0STAT & UCBUSY);
   do{

      UCB0STAT = 0x00;
      UCB0CTL1 |= UCTR;
      UCB0CTL1 &= ~UCTXSTT;
      UCB0CTL1 |= UCTXSTT;
      while(UCB0CTL1 & UCTXSTT){
        if(!(UCNACKIFG & UCB0STAT))break;
      }
      UCB0CTL1 |= UCTXSTP;
      while (UCB0CTL1 & UCTXSTP);
    }while(UCNACKIFG & UCB0STAT);
}
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR_HOOK(void){
    short end = 0;
    if( UCB0CTL0 & UCMODE_3 ){
       if (IFG2 & UCB0TXIFG){
         end = I2C_tx_handler();
         if(end){ 
             __bic_SR_register_on_exit(LPM0_bits + GIE);
         }
      }
      else if(IFG2 & UCB0RXIFG){
          end = I2C_rx_handler();
          if(end) 
             __bic_SR_register_on_exit(LPM0_bits + GIE);
      }
    }
    else{
        __bic_SR_register_on_exit(LPM0_bits + GIE);
    }
}
