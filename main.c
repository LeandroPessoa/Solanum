/*
 * 
 * Firmware Solanum para nó sensor - Projeto agricultura de precisão
 * 
 * 
*/


#include  <msp430g2553.h>
#include "timer.c"
#include "clock.c"
#include "interrupts.c"
#include "io.c"
#include "flash.c"
#include "i2cmaster.c"
#include "uart.c"
 
/**
 * 
 * DEFINES DEVEM SER CONTIDOS AQUI
 * 
 * Inicio
*/
#define  BYTE_LOW 0
#define  BYTE_HIGH 1

/**
 * 
 * Tempo entre amostragens em segundos.
 * tempo padrao 675
 */
#define AMOSTRAR 1

#define NADA 7
#define ZERAR 6
#define ENVIANDO 5
#define PISCAR 4
#define DESCARREGAR 3
#define CHECARMEMORIA 2
#define GRAVAR 1
#define STANDBY 0 

#define UMSEGUNDO 4095
#define MEIOSEGUNDO 1023



/**
 * 
 * FIM defines
*/

/**
 * 
 * VARIAVEIS GLOBAIS DEVEM SER CONTIDAS AQUI.
 * Inicio
 * 
 */
unsigned int contador = 0;
unsigned int contadorTemperaturas = 0;

unsigned char RxBuffer[32];        // Receive data array
unsigned char *PRxData = RxBuffer; // Pointer to RX data array
unsigned char RXByteCtr = 0;       // RX byte count

/**
 * Estado inicial dos buffers para identificar durante debug se gravação foi realizada.
 * 
 **/

unsigned char bufferFlashD[64] = "----------------------------------------------------------------";
unsigned char bufferFlashC[64] = "----------------------------------------------------------------";

/*
 * Buffer os bytes correspondentes a leitura de temperatura obtida.
 * */
unsigned char bufferTemperatura[2] = "";
unsigned char bufferAmbiente[2] = "";

/*
 * Variável modo recebe modo de operação corrente, deve se iniciar com CHECARMEMORIA para avaliar se a memoria está cheia.
 * */

unsigned char modo = CHECARMEMORIA;

/**
 * Flag de estados que sinaliza quando aquisiçoes de temperaturas podem ser feitas.
 * Não usado|Não usado|Não usado|Não usado|Não usado|Não usado|Não usado|Memoria Cheia|
 * 
 * 
*/
char flag = 0;


/*
 * Função faz do nó sensor elemento inoperante aguardando ser reiniciado para iniciar protocolo de aquisição de dados.
 */
void nada(void)
{
  
 while(1) ;
  
}
/*
 * Função que pisca led para fins de verificação de funcionamento
 */
void justPiscar(void)
{
 P1OUT ^= 1;

 LPM3;
  
}
/*
 * Função reconfigura tempo de oscilação de led para sinalizar fim de aquisiçoes de temperaturas indicado que a memoria deve ser descarregada
 */
void descarregar(void)
{
  
  Timer1_A3_init(MEIOSEGUNDO);
  
}
/*
 * Função responsável pela gravação de dados em memoria flash. É responsável por alternar para modo DESCARREGAR indicando para o usuário
 * o fim das ações de aquisição.
 */
void gravar(void)
 {
   
   writeSegD(bufferFlashD);
   writeSegC(bufferFlashC);
   modo = DESCARREGAR;  
   
 }
 /*
  * Função responsável por transmitir via protocolo serial dados contidos na memoria e sinalizar esse envio através de led. Retorna para o modo PISCAR.
  */
 void enviando()
 {
   unsigned int i = 0;
  for(i; i < 128; i++)
  {
    
sendData(readAddress(i));

    
  }
  modo = PISCAR;
   
 }
 /*
  * Zera flag presente na memoria que sinaliza se a memoria destinada as aquisiçoes está cheia.
  */
 void zerar()
 {
   
   char flag = 0x00;
   writeFlag(&flag);
   modo = NADA;
   
   
 }
 /*
  * Verifica flag armazenado em memoria flash para averiguar se aquisições de temperatura devem ser feitas ou não
  */
 void checarMemoria()
 {
   __delay_cycles(600000);
   if(readFlag() & BIT0)
   {
    timerStop();
   modo = DESCARREGAR;
     
  }
    else
   {
     timerStart();
     modo = STANDBY;
   }
   
 }
 
 
 
void main(void)
{
  
	/*!
	Rotinas de inicializaçao de dispositivo embarcado
	*/
	
	
	/*!
	Desliga watchdog timer.
	*/
	WDTCTL = WDTPW + WDTHOLD;			
	
	/*!
	Configura entradas/saidas.
	*/
	GPIO_init();
	uartInit();
	/*!
	Configura capacitores para crystal de 32768hz
	*/
	BCSplus_init();				
 
	/*!
	Configurações de gravação em memoria flash
	*/
    initFlash();


	Timer1_A3_init(UMSEGUNDO);
	
	I2C_init(0x15);

	
	
	System_init();
	int i = 0;
	LPM3;
  
	 while(1)
  {

    
 switch(modo)
 {
   case GRAVAR:
     gravar();
     break;
   case CHECARMEMORIA:
     checarMemoria();
     break;
   case DESCARREGAR:
     descarregar();
     break;
   case PISCAR:
     justPiscar();
     break;
   case ENVIANDO:
     enviando();
     break;
   case ZERAR:
     zerar();
     break;
   case NADA:
     nada();
     break;
   default:
    justPiscar();
     break;
     
   
 }
 
    /** 
 if(modo == GRAVAR)
 {
 writeSegD(buffCHECARMEMORIAerFlash);
 modo = STANDBY; 
 }
 P1OUT ^= 1;
 LPM3;
 */
 
  }
	
}

 
 
 /*
  * Rotina para aquisição de temperatura.
  */
 void lerSensor(unsigned char* buffer)
 {
   unsigned char cmd = 0x07;
  int i;
  unsigned char leitura[3];
   I2C_ack_polling();
    I2C_send_data(0x00,&cmd,1,0);
    I2C_receive_data(0x00,leitura,3);
    //int temperatura = leitura[BYTE_LOW];
    //temperatura = temperatura << 8;
   // temperatura |= leitura[BYTE_HIGH];
   *buffer = leitura[BYTE_LOW];
   buffer++;
   *buffer = leitura[BYTE_HIGH];
    //sendData(0x21);
   
 }

 void lerAmbiente(unsigned char* buffer)
 {
   unsigned char cmd = 0x06;
  int i;
  unsigned char leitura[3];
   I2C_ack_polling();
    I2C_send_data(0x00,&cmd,1,0);
    I2C_receive_data(0x00,leitura,3);
    //int temperatura = leitura[BYTE_LOW];
    //temperatura = temperatura << 8;
   // temperatura |= leitura[BYTE_HIGH];
   *buffer = leitura[BYTE_LOW];
   buffer++;
   *buffer = leitura[BYTE_HIGH];
    //sendData(0x21);
   
 }


/*
 *  ======== USCI A0/B0 RX Interrupt Handler Ge| BIT0neration ========
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void)
{
if(UCA0RXBUF == 'a')
{
 modo = ENVIANDO; 
  
  
}
else
  if(UCA0RXBUF == 'b')
  {
    modo = ZERAR;
    
  }
  

}
/*
 *  ======== Timer1_A3 Interrupt Service Routine ======== 
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void)
{

  if(modo == STANDBY)
  {
  
  if(contador == AMOSTRAR)
  {
lerSensor(bufferTemperatura);
lerAmbiente(bufferAmbiente);

  
bufferFlashD[contadorTemperaturas] = bufferTemperatura[0];
bufferFlashD[contadorTemperaturas + 1] = bufferTemperatura[1];
bufferFlashC[contadorTemperaturas] = bufferAmbiente[0];
bufferFlashC[contadorTemperaturas + 1] = bufferAmbiente[1]; 
    
  
contadorTemperaturas = contadorTemperaturas + 2;

if(contadorTemperaturas == 64)
{

modo = GRAVAR;
flag |= BIT0;
writeFlag(&flag);
timerStop();
 __bic_SR_register_on_exit(LPM3_bits);
} 
contador = 0;

  }
  contador++;
 
  }
  else
    if(modo == DESCARREGAR)
    {
     modo = PISCAR;
      
      
    }
  __bic_SR_register_on_exit(LPM3_bits);
}


 
