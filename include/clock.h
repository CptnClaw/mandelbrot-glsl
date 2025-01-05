#ifndef CLOCK_H_
#define CLOCK_H_

class Clock
{
    public:
        // Initailizes a clock and registers current time
        Clock();

        // Calculates time passed since last call (or since initialization)
        // in seconds
        float tick();

    private:
        float prev_time;
        float prev_fps_print;
        int frame_counter;
};

#endif // CLOCK_H_