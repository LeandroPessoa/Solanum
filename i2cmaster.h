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
 * @file I2C_Master.h
 * @brief A biblioteca I2C_MASTER tem o objetivo de possibilitar uma comunicacao via
 * I2C
 */

#ifndef _I2C_MASTER_
#define _I2C_MASTER_

/** @def  I2C_PORT_SEL P3SEL
 * Seleciona P3
 */
#define I2C_PORT_SEL  P1SEL

/** @def  I2C_PORT_OUT P3OUT
 * Saida de P3
 */
#define I2C_PORT_OUT  P1OUT

/** @def I2C_PORT_DIR P3DIR
 * Direciona P3
 */
#define I2C_PORT_DIR  P1DIR

/** @def SDA_PIN BIT1
 * pino SDA
 */
#define SDA_PIN  BIT7

/** @def SCL_PIN BIT2
 * pino SCL
 */
#define SCL_PIN  BIT6

/** @def SCL_CLOCK_DIV 0x12
 * bit de divisao de clock SCL
 */
#define SCL_CLOCK_DIV 0x12

/**@var extern unsigned char *pointer_rx_data
 * @brief Ponteiro para armazenar
 * os dados recebidos
 */
extern unsigned char *pointer_rx_data;

/**@var extern unsigned char *pointer_tx_data
 * @brief Ponteiro para dados a serem enviados
 */
extern unsigned char *pointer_tx_data;

/**@var extern int tx_byte_ctr
 * @brief Contador de bytes a serem enviados
 */
extern int tx_byte_ctr;

/** @var extern int rx_byte_ctr
 *  @brief Contador de bytes a serem recebidos
 */
extern int rx_byte_ctr;

/**
 * @fn void I2C_init(unsigned char own_address)
 * @brief Inicializa comunicação I2C com dispositivo escravo
 * @param unsigned char own_address - Variavel referente ao endereco do dispositivo
 * @return Esta funcao nao possui retorno
 */
void I2C_init(unsigned char own_address);

/**@fn void I2C_send_data(unsigned char slave_address,unsigned char* tx_data,int num_bytes,unsigned char send_stop)
* @brief Envia dados para dispositivo escravo  desejado
* @param unsigned char slave_address - Varialvel referente ao endereço do dispositivo receptor da 
*msg a ser enviada.
* @param unsigned char* tx_data - Ponteiro referente aos dados a serem enviados
* @param int num_bytes - Variavel referente a quantidade de bytes a serem enviados
* @return Esta funcao nao possui retorno
*/
void I2C_send_data(unsigned char slave_address,unsigned char* tx_data,unsigned int num_bytes,unsigned char send_stop);

/**
* @fn void I2C_receive_data(unsigned char slave_address,unsigned char* rx_data,int num_bytes)
* @brief Recebe dados do dispositivo escravo desejado
* @param unsigned char slave_address - Variavel referente ao endereço do dispositivo emissor
* da msg a ser recebida.
* @param unsigned char* rx_data - Variavel referente aos dados a serem recebidos
* @param int num_bytes - Variavel referente a quantidade de bytes a serem recebidos
* @return Esta funcao nao possui retorno
*/
void I2C_receive_data(unsigned char slave_address,unsigned char* rx_data,unsigned int num_bytes);

/**
* @fn int I2C_tx_handler(void)
* @brief Trata a interrupcao de envio de mensagem
* @return Retorna um valor int (0 ou 1)
*/
short I2C_tx_handler(void);

/**
* @fn int I2C_rx_handler(void)
* @brief Trata a interrupcao de recebimento de mensagem
* @return Retorna um valor int (0 ou 1)
*/
short I2C_rx_handler(void);

/**
 * @fn void I2C_AckPolling()
 * @brief Verifica se I2C esta ocupada em modo de escrita
 * @return esta funcao nao possui retorno
 */
void I2C_ack_polling();

#endif
