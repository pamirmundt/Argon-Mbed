/**
  ******************************************************************************
  * @file    hal_inits.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_INITS_H
#define __HAL_INITS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Private define ------------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define M1_CUR_SENS_Pin GPIO_PIN_0
#define M1_CUR_SENS_GPIO_Port GPIOC
#define M2_CUR_SENS_Pin GPIO_PIN_1
#define M2_CUR_SENS_GPIO_Port GPIOC
#define M3_CUR_SENS_Pin GPIO_PIN_2
#define M3_CUR_SENS_GPIO_Port GPIOC
#define M4_CUR_SENS_Pin GPIO_PIN_3
#define M4_CUR_SENS_GPIO_Port GPIOC
#define M1_ENC_A_Pin GPIO_PIN_0
#define M1_ENC_A_GPIO_Port GPIOA
#define M1_ENC_B_Pin GPIO_PIN_1
#define M1_ENC_B_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define M3_ENC_A_Pin GPIO_PIN_6
#define M3_ENC_A_GPIO_Port GPIOA
#define M3_ENC_B_Pin GPIO_PIN_7
#define M3_ENC_B_GPIO_Port GPIOA
#define M5_CUR_SENS_Pin GPIO_PIN_4
#define M5_CUR_SENS_GPIO_Port GPIOC
#define M6_CUR_SENS_Pin GPIO_PIN_5
#define M6_CUR_SENS_GPIO_Port GPIOC
#define M4_ENC_A_Pin GPIO_PIN_0
#define M4_ENC_A_GPIO_Port GPIOB
#define M4_ENC_B_Pin GPIO_PIN_1
#define M4_ENC_B_GPIO_Port GPIOB
#define M2_ENC_B_Pin GPIO_PIN_2
#define M2_ENC_B_GPIO_Port GPIOB
#define M2_ENC_A_Pin GPIO_PIN_10
#define M2_ENC_A_GPIO_Port GPIOB
#define M5_DIR_PIN_Pin GPIO_PIN_12
#define M5_DIR_PIN_GPIO_Port GPIOB
#define M6_DIR_PIN_Pin GPIO_PIN_13
#define M6_DIR_PIN_GPIO_Port GPIOB
#define M5_PWM_Pin GPIO_PIN_14
#define M5_PWM_GPIO_Port GPIOB
#define M6_PWM_Pin GPIO_PIN_15
#define M6_PWM_GPIO_Port GPIOB
#define M1_PWM_Pin GPIO_PIN_6
#define M1_PWM_GPIO_Port GPIOC
#define M2_PWM_Pin GPIO_PIN_7
#define M2_PWM_GPIO_Port GPIOC
#define M3_PWM_Pin GPIO_PIN_8
#define M3_PWM_GPIO_Port GPIOC
#define M4_PWM_Pin GPIO_PIN_9
#define M4_PWM_GPIO_Port GPIOC
#define M5_LIM_SW_Pin GPIO_PIN_8
#define M5_LIM_SW_GPIO_Port GPIOA
#define M4_DIR_PIN_Pin GPIO_PIN_11
#define M4_DIR_PIN_GPIO_Port GPIOA
#define M3_DIR_PIN_Pin GPIO_PIN_12
#define M3_DIR_PIN_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define M4_LIM_SW_Pin GPIO_PIN_15
#define M4_LIM_SW_GPIO_Port GPIOA
#define M3_LIM_SW_Pin GPIO_PIN_10
#define M3_LIM_SW_GPIO_Port GPIOC
#define M2_LIM_SW_Pin GPIO_PIN_11
#define M2_LIM_SW_GPIO_Port GPIOC
#define M1_LIM_SW_Pin GPIO_PIN_12
#define M1_LIM_SW_GPIO_Port GPIOC
#define M2_DIR_PIN_Pin GPIO_PIN_2
#define M2_DIR_PIN_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define M6_LIM_SW_Pin GPIO_PIN_4
#define M6_LIM_SW_GPIO_Port GPIOB
#define M1_DIR_PIN_Pin GPIO_PIN_5
#define M1_DIR_PIN_GPIO_Port GPIOB
#define M5_ENC_A_Pin GPIO_PIN_6
#define M5_ENC_A_GPIO_Port GPIOB
#define M5_ENC_B_Pin GPIO_PIN_7
#define M5_ENC_B_GPIO_Port GPIOB
#define M6_ENC_A_Pin GPIO_PIN_8
#define M6_ENC_A_GPIO_Port GPIOB
#define M6_ENC_B_Pin GPIO_PIN_9
#define M6_ENC_B_GPIO_Port GPIOB
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void _Error_Handler(const char * file, int line);

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base);

/* ADC1 init function Here!*/
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM6_Init(void);
void MX_TIM8_Init(void);
void MX_TIM12_Init(void);

void MX_GPIO_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __INIT_H */