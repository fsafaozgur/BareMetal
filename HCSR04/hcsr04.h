#ifndef __HCSR04_H
#define __HCSR04_H

  void HCSR04_Init(void);
  uint16_t read_distance(void);
  void wait_us(uint16_t delay);

#endif /* __HCSR04_H */
