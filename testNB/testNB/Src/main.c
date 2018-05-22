/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "NBBC95.h"
#include "NBBC95_cfg.h"
#include "uartTimerPoll.h"
#include "stdint.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
typedef enum {
    NB_NONE,
    NB_Init,
    NB_Module,
    NB_SIGN,
    NB_UDP_Create,
    NB_UDP_Send,
    NB_UDP_Read,
    NB_UDP_Close,
    NB_Coap_Server,
    NB_Coap_Send,
    NB_Coap_Read,
    NB_Reset,
    NB_END
}NB_State;


uint8_t* NB_MODULE_IMEI = NULL;

//记录NB模块流程
uint8_t processRecord = 0;

#define NB_PROCESS_INIT             0X01
#define NB_PROCESS_UDP_CREATE       0x02
#define NB_PROCESS_UDP_REG          0x04
#define NB_PROCESS_COAP_SERVER      0x08

volatile NB_State nb_state = NB_NONE;
int NB_MsgreportCallback(msg_type, int, char*);
void readNBStateFromUart(void);
uint8_t receBufferPC[1];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
    openNBModule(&bc95_cfg);
    nb_state = NB_NONE;
    HAL_UART_Receive_IT(&huart2, (uint8_t*)receBufferPC, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
      //HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"test", 4);
      //HAL_USART_Write((uint8_t*)"AT\r\n", 4);
    HAL_USART_Poll();
    bc95Main(&bc95_cfg);
    TimerPoll();
    
    
    switch(nb_state) {
        case NB_NONE:
            break;
        case NB_Init: {
            printf("\r\n BC95 Module is initializing...");
            processRecord = 0;
            initNBModule(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_SIGN: {
            printf("\r\n BC95 Module sign state:");
            SignNBModule(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_Module: {
            printf("\r\n BC95 Module info:");
            getModuleInfoNBModule(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_UDP_Create: {
            printf("\r\n BC95 Module Create UDP server");
            createUDPServerNBModule(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_UDP_Send: {
            printf("\r\n BC95 Module Send Messsage to UDP Server");
            //char* userPacket = "test\r\n";
            sendToUdpNBModule(&bc95_cfg, 10, "test\r\n");
            nb_state = NB_END;
            break;
        }
        case NB_UDP_Read: {
            printf("\r\n BC95 Module is initializing...");
            recFromUdp_bc95(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_UDP_Close: {
            printf("\r\n BC95 Module close UDP server");
            closeUdpNBModule(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_Coap_Server: {
            printf("\r\n BC95 Module is Creating Coap server...");
            coapServerNBModule(&bc95_cfg, 1, NULL);
            nb_state = NB_END;
            break;
        }
        case NB_Coap_Read: {
            printf("\r\n BC95 Module is initializing...");
            initbc95(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        case NB_Coap_Send: {
            printf("\r\n BC95 Module is Sending msg using Coap Server...");
            coapSentMsgNBModule(&bc95_cfg, sizeof("testCoap"), "testCoap");
            nb_state = NB_END;
            break;
        }
        
        case NB_Reset: {
            printf("\r\n BC95 Module is initializing...");
            initNBModule(&bc95_cfg);
            nb_state = NB_END;
            break;
        }
        default:
            break;
    }
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
}

/* USER CODE BEGIN 4 */
int NB_MsgreportCallback(msg_type mType, int len, char* msg)
{
    //printf("\r\nmsg:%s", msg);
    switch(mType) {
        case MSG_INIT:
            printf("\r\nInit:%s", msg);
            if (*msg == 'S') {
                printf("\r\n初始化成功");
                processRecord |= NB_PROCESS_INIT;
                nb_state = NB_UDP_Create;
            }
            break;
        case MSG_IMSI:
            printf("\r\nIMSI:%s", msg);
            break;
        case MSG_IMEI:
            printf("\r\nIMEI:%s", msg);
            NB_MODULE_IMEI = (uint8_t*)msg;
            break;
        case MSG_SIGN:
            printf("\r\nSIGN:%s", msg);
            break;
        case MSG_DEVID:
            printf("\r\nDEVID:%s", msg);
            break;
        case MSG_MANUINFO:
            printf("\r\nMANUINFO:%s", msg);
            break;
        case MSG_REGISTER:
            printf("\r\nREGISTER:%s", msg);
            break;
        case MSG_UDP_CREATE:
            printf("\r\nUDP Create:%s", msg);
            if (*msg == 'S'){
                printf("\r\nUDP初始化成功");
                processRecord |= NB_PROCESS_UDP_CREATE;
                nb_state = NB_UDP_Send;
            }
            break;
        case MSG_UDP_SEND:
            printf("\r\nUDP Send:%s", msg);
            if (*msg == 'S'){
                printf("\r\nUDP发送数据成功");
                //如果需要接收数据则继续调用接受函数recFromUdp_bc95，发送接受指令
            }
            break;
        case MSG_UDP_RECE:
            printf("\r\nUDP Receive:%s", msg);
            if (*msg == 'S'){
                printf("\r\nUDP接收数据成功");
            }
            break;
        case MSG_UDP_CLOSE:
            printf("\r\nUDP Close:%s", msg);
            if (*msg == 'S'){
                printf("\r\nUDP关闭");
                processRecord &= ~NB_PROCESS_UDP_CREATE;
            }
            break;
        case MSG_COAP:
            printf("\r\nCoap Create:%s", msg);
            if (*msg == 'S'){
                printf("\r\nUDP初始化成功");
                processRecord |= NB_PROCESS_COAP_SERVER;
            }
            break;
        case MSG_COAP_SEND:
            printf("\r\nCoap Send:%s", msg);
            if (*msg == 'S'){
                printf("\r\nCoap发送数据成功");
                //如果需要接收数据则继续调用接受函数recFromCoap_bc95，发送接受指令
            }
            break;
        default: 
            break;
    }
    return 0;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    //printf("recevied");
    //HAL_UART_Transmit_IT(&huart2, (uint8_t *)receBufferPC, 1);
    //HAL_Delay(10);
    if (huart == &huart2) {
        readNBStateFromUart();
        receBufferPC[0] = 0x00;
        HAL_UART_Receive_IT(&huart2, (uint8_t*)receBufferPC, 1);
        
    }
}


void readNBStateFromUart(void)
{
    if (receBufferPC[0] == '1') {
        nb_state = NB_Init;
    }
    else if (receBufferPC[0] == '2') {
        if (processRecord & NB_PROCESS_INIT)
            nb_state = NB_SIGN;
    }
        
    else if (receBufferPC[0] == '3') {
        if (processRecord & NB_PROCESS_INIT)
            nb_state = NB_Module;
    }
    else if (receBufferPC[0] == '4') {
        if (processRecord & NB_PROCESS_INIT)
            nb_state = NB_UDP_Create;
    }
    else if (receBufferPC[0] == '5') {
        if (processRecord & NB_PROCESS_INIT) {
            if (processRecord & NB_PROCESS_UDP_CREATE)
                nb_state = NB_UDP_Send;
        }
    }
    else if (receBufferPC[0] == '6')
        nb_state = NB_UDP_Read;
    else if (receBufferPC[0] == '7')
        nb_state = NB_UDP_Close;
    else if (receBufferPC[0] == '8') {
        if (processRecord & NB_PROCESS_INIT)
            if (!(processRecord & NB_Coap_Server))
            nb_state = NB_Coap_Server;
    }
    else if (receBufferPC[0] == '9') {
        if (processRecord & NB_Coap_Server)
            nb_state = NB_Coap_Send;
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
