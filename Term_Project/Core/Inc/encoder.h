
class Encoder {
    public:
        Encoder(int pinA, int pin8);

        void enable();
        void disable();
        void update();

        void getPosition() const;
        void setPosition(float pos);
        void reset();

    private:
        int pinA_;
        int pinB_;
        float position_;
        int state_;

};
