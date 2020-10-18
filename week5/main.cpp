#include <hwlib.hpp>

int main() {

    auto pin = hwlib::target::pin_out(hwlib::target::pins::led);

    for (;;) {
        hwlib::blink(pin);
    }
}