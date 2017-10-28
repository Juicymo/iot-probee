
// FSM Definition (see fsm_reasoning.png)
NEW_STATE(idle);
NEW_STATE(scanning);
NEW_STATE(reasoning);
NEW_STATE(backward);
NEW_STATE(forward);
NEW_STATE(fast_forward);
NEW_STATE(turn_left);
NEW_STATE(turn_right);

FSM fsm_reasoning = FSM(idle);

bool state = false;
unsigned long time;
unsigned int current_step;
unsigned int steps[STEPS + 1] = {1000, 1000};

// Private

// IDLE ----------------------------------------------------------------------------
STATE_ENTER(idle) {
	TRACE("idle enter");
	
	hal_motor_stop(M_L);
	hal_motor_stop(M_R);
}

STATE_UPDATE(idle) {
	if (fsm.timeInCurrentState() > 500) {
		//fsm.transitionTo(scanning);
		fsm.transitionTo(reasoning);
	}
	
	hal_motor_drive(M_L, speed_left);
	hal_motor_drive(M_R, speed_right);
}

STATE_EXIT(idle) {
}

// SCANNING ----------------------------------------------------------------------------
STATE_ENTER(scanning) {
	TRACE("scanning enter");
	
	hal_servo_scan_full_reset();
}

STATE_UPDATE(scanning) {
	hal_servo_scan_full();
	hal_sensors_ultrasonic_turret_scan();
}

STATE_EXIT(scanning) {
}

// ----------------------------------------------------------------------------
STATE_ENTER(learning)
{
	TRACE("lerning_enter");
	current_step = 0;
	color(YELLOW);
}

STATE_UPDATE(learning)
{
	if (fsm.timeInCurrentState() > 500)
	{
		color(BLACK);
	}

	if (btnA.fallingEdge())
	{
		fsm.transitionTo(learning_on);
	}
}

STATE_EXIT(learning)
{
}

// ----------------------------------------------------------------------------

bool save_step()
{
	steps[current_step] = fsm.timeInCurrentState();
	current_step++;

	if (current_step >= STEPS)
	{
		return false;
	}

	return true;
}


STATE_ENTER(learning_on)
{
	TRACE("lerning_on_enter");
	color(WHITE);
}

STATE_UPDATE(learning_on)
{
	if (btnA.risingEdge())
	{
		if (save_step())
		{
			fsm.transitionTo(learning_off);
		}
		else
		{
			fsm.transitionTo(learning_done);
		}
	}
}

STATE_EXIT(learning_on)
{
}

// ----------------------------------------------------------------------------

STATE_ENTER(learning_off)
{
	TRACE("lerning_off_enter");
	color(BLACK);
}

STATE_UPDATE(learning_off)
{
	if (btnA.fallingEdge())
	{
		if (save_step())
		{
			fsm.transitionTo(learning_on);
		}
		else
		{
			fsm.transitionTo(learning_done);
		}
	}

	if (btnB.fallingEdge()){
		save_step();
		fsm.transitionTo(learning_done);
	}
}

STATE_EXIT(learning_off)
{
}

// ----------------------------------------------------------------------------

STATE_ENTER(learning_done)
{
	TRACE("lerning_done_enter");

	if (current_step < STEPS)
	{
		color(GREEN);
	}
	else
	{
		color(0xFF, 0, 0);
	}

	steps[current_step] = 0;
}

STATE_UPDATE(learning_done)
{
	if (fsm.timeInCurrentState() > 1000)
	{
		color(BLACK);
		fsm.transitionTo(blinking);
	}
}

STATE_EXIT(learning_done)
{
}


// Public
void setup_state_machine() {
	TRACELN('fsm_reasoning initialized')
}

void state_machine_loop() {
	fsm_reasoning.update();
}