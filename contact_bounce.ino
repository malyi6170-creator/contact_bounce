#include <avr/io.h>

#define LED_PIN   PB0  // Светодиод подключен к PB0 (ножка 5)
#define BUTTON_PIN PB1 // Кнопка подключена к PB1 (ножка 6)

int main(void) {
    // Настройка выводов
    DDRB |= (1 << LED_PIN);    // PB0 на выход (LED)
    DDRB &= ~(1 << BUTTON_PIN); // PB1 на вход (Кнопка)
    PORTB |= (1 << BUTTON_PIN); // Включаем внутреннюю подтяжку (PULL-UP) на PB1

    uint8_t last_state = (PINB & (1 << BUTTON_PIN));

    while (1) {
        uint8_t current_state = (PINB & (1 << BUTTON_PIN));

        // Фиксируем СПАД сигнала (переход от HIGH к LOW — нажатие на землю)
        // Никакой защиты от дребезга (no debounce) и никаких задержек!
        if (last_state && !current_state) {
            PORTB ^= (1 << LED_PIN); // Тогглим состояние светодиода
        }

        last_state = current_state;
    }

    return 0;
}
