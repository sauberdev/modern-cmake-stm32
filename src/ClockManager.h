//
// Created by sauber on 27.03.20.
//

class ClockManager {
public:
    /**
     * @brief Setups the system to use external clock and configures desired frequencies
     * @note This code is copied from generated main.c and should be platform dependent
     */
    static bool init();

private:
    /**
     * @brief Private constructor of class ClockManager.
     * @note Constructor defined as private as it's a static class.
     */
    ClockManager() = default;
};
