class LimitSwitch{
public:
	LimitSwitch(GPIO_TypeDef *port, uint16_t pin, uint8_t activeMode = 0, uint8_t pudMode = 0, bool interruptMode = false);


	bool init(void);

	void clean(void);

	void read(void);

	bool get(void) {return _state;};

	void EXTI_Callback(void);


private:
	bool _initState;
	volatile bool _state;

	GPIO_TypeDef *_GPIO_PORT;

	uint16_t _GPIO_PIN;
	uint8_t _ACTIVE_MODE;

	bool _interruptMode;

	bool _RCC_GPIO_CLK_ENABLE(GPIO_TypeDef *GPIO_PORT);
};
