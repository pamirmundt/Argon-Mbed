#ifndef HAL_IT_H
#define HAL_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
