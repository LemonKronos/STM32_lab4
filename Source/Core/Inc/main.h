/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_0_Pin GPIO_PIN_0
#define BUTTON_0_GPIO_Port GPIOA
#define BUTTON_1_Pin GPIO_PIN_1
#define BUTTON_1_GPIO_Port GPIOA
#define BUTTON_2_Pin GPIO_PIN_2
#define BUTTON_2_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_3
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_4
#define EN1_GPIO_Port GPIOA
#define EN2_Pin GPIO_PIN_5
#define EN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_6
#define EN3_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_7
#define SEG0_GPIO_Port GPIOA
#define LED0_R_Pin GPIO_PIN_0
#define LED0_R_GPIO_Port GPIOB
#define LED0_Y_Pin GPIO_PIN_1
#define LED0_Y_GPIO_Port GPIOB
#define LED0_G_Pin GPIO_PIN_2
#define LED0_G_GPIO_Port GPIOB
#define SEG1_Pin GPIO_PIN_8
#define SEG1_GPIO_Port GPIOA
#define SEG2_Pin GPIO_PIN_9
#define SEG2_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_10
#define SEG3_GPIO_Port GPIOA
#define SEG4_Pin GPIO_PIN_11
#define SEG4_GPIO_Port GPIOA
#define SEG5_Pin GPIO_PIN_12
#define SEG5_GPIO_Port GPIOA
#define SEG6_Pin GPIO_PIN_13
#define SEG6_GPIO_Port GPIOA
#define TEST_Timer_Pin GPIO_PIN_14
#define TEST_Timer_GPIO_Port GPIOA
#define TEST_Button_Pin GPIO_PIN_15
#define TEST_Button_GPIO_Port GPIOA
#define LED1_R_Pin GPIO_PIN_3
#define LED1_R_GPIO_Port GPIOB
#define LED1_Y_Pin GPIO_PIN_4
#define LED1_Y_GPIO_Port GPIOB
#define LED1_G_Pin GPIO_PIN_5
#define LED1_G_GPIO_Port GPIOB
#define timerP_Pin GPIO_PIN_6
#define timerP_GPIO_Port GPIOB
#define TEST_Pin GPIO_PIN_7
#define TEST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
