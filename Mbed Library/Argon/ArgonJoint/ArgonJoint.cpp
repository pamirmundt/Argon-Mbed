#include "ArgonJoint.h"
#include "hal_inits.h"
//#include "ArgonJointParams.h"

#ifndef M_PI
#define M_PI        3.14159265358979323846f
#endif

#ifndef RPM2RAD
#define RPM2RAD     ((2.0f*M_PI)/60.0f)
#endif

#ifndef REV2RAD
#define REV2RAD    (2.0f * M_PI)
#endif

using namespace argon;

int8_t encoderIndex[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

TIM_HandleTypeDef * argon::_getRpmCalcTimer(void){
    return ArgonJointParams::rpm_calc_timer;
}

/* SETS */
// Config
void ArgonJoint::_setAvailable(bool available){
    this->_available = available;
}

void ArgonJoint::_setGearRatio(float gearRatio){
    this->_gearRatio = gearRatio;
}

void ArgonJoint::_setEncoderTicksPerRound(uint16_t encoderTicksPerRound){
    this->_encoderTicksPerRound = encoderTicksPerRound;
}

void ArgonJoint::_setEncodingMode(uint8_t encodingType){
    this->_encodingType = encodingType;
}

void ArgonJoint::_setEncoderIndex(uint8_t encoderIndex){
    this->_encoderIndex = encoderIndex;
}

void ArgonJoint::_setEncoderCount(int32_t encoderCount){
    this->_encoderCount = encoderCount;
}

void ArgonJoint::_setPrevEncoderCount(int32_t prevEncoderCount){
    this->_prevEncoderCount = prevEncoderCount;
}

void ArgonJoint::_setMotorRPM(float motorRPM){
    this->_motorRPM = motorRPM;
}

void ArgonJoint::_setJointRPM(float jointRPM){
    this->_jointRPM = jointRPM;
}

void ArgonJoint::_setMotorPosition(float motorPosition){
    this->_motorPosition = motorPosition;
}

// Functions
void ArgonJoint::setPWM(int16_t PWM){
    this->_PWM = PWM;
    this->_power = (float(PWM)/float(_pwmResolution))*100.0f;

    if(PWM > 0){
        this->_direction = 0;
        HAL_GPIO_WritePin(this->_directionPort, this->_directionPin, GPIO_PIN_SET);  
    }
    else if (PWM < 0){
        this->_direction = 1;
        HAL_GPIO_WritePin(this->_directionPort, this->_directionPin, GPIO_PIN_RESET);
    }

    __HAL_TIM_SET_COMPARE(_getPwmTimer(), _getPwmTimerChannel(), abs(PWM));
}

void ArgonJoint::setPower(float power){
    this->_power = power;
    setPWM(int16_t(power * _pwmResolution / 100.0f));
}

/* Gets */
uint8_t ArgonJoint::_getEncoderIndex(void){
    return this->_encoderIndex;
}

bool ArgonJoint::getAvailable(void){
    return this->_available;
}

uint8_t ArgonJoint::getNumber(void){
    return this->_number;
}

float ArgonJoint::getGearRatio(void){
    return this->_gearRatio;
}

uint16_t ArgonJoint::getEncoderTicksPerRound(void){
    return this->_encoderTicksPerRound;
}

uint8_t ArgonJoint::getEncodingMode(void){
    return this->_encodingType;
}

// Functions
int16_t ArgonJoint::getPwm(void){
    return this->_PWM;
}

uint16_t ArgonJoint::getPwmResolution(void){
    return this->_pwmResolution;
}

float ArgonJoint::getPower(void){
    return this->_power;
}

int8_t ArgonJoint::getDirection(void){
    return this->_direction;
}

//Position
int32_t ArgonJoint::getEncoderCount(void){
    return this->_encoderCount;
}

int32_t ArgonJoint::_getPrevEncoderCount(void){
    return this->_prevEncoderCount;    
}

float ArgonJoint::getJointPosition(void){
    return (this->getMotorPosition() / this->_gearRatio);
}

float ArgonJoint::getMotorPosition(void){
    return (this->_motorPosition);
}

//RPM
float ArgonJoint::getMotorRPM(void){
    return this->_motorRPM;
}

float ArgonJoint::getJointRPM(void){
    return (this->getMotorRPM() / this->_gearRatio);
}

//Angular Velocity
float ArgonJoint::getMotorAngVel(void){
    return (this->getMotorRPM() * RPM2RAD);
}

float ArgonJoint::getJointAngVel(void){
    return (this->getMotorAngVel() / this->_gearRatio);
}

// Encoder Reading
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    // TIM2
    // Joint 1 - 2
    if( htim->Instance == TIM2 ){
        // Joint 1
        if((htim->Channel == ArgonJointParams::joint1_ic_timer_act_CH_A) || (htim->Channel == ArgonJointParams::joint1_ic_timer_act_CH_B)){
            uint8_t readA = HAL_GPIO_ReadPin(M1_ENC_A_GPIO_Port, M1_ENC_A_Pin);
            uint8_t readB = HAL_GPIO_ReadPin(M1_ENC_B_GPIO_Port, M1_ENC_B_Pin);
            
            uint8_t idx = ArgonJoint::joint1_Instance()._getEncoderIndex();
            uint8_t enc_idx = (( idx << 2) & 0x0F) + (readA << 1) + readB;
            ArgonJoint::joint1_Instance()._setEncoderIndex(enc_idx);
            
            int32_t encoderCount = ArgonJoint::joint1_Instance().getEncoderCount();
            encoderCount = encoderCount + encoderIndex[enc_idx];
            ArgonJoint::joint1_Instance()._setEncoderCount(encoderCount);
        }
        
        // Joint 2
        if((htim->Channel == ArgonJointParams::joint2_ic_timer_act_CH_A) || (htim->Channel == ArgonJointParams::joint2_ic_timer_act_CH_B)){
            
            uint8_t readA = HAL_GPIO_ReadPin(M2_ENC_A_GPIO_Port, M2_ENC_A_Pin);
            uint8_t readB = HAL_GPIO_ReadPin(M2_ENC_B_GPIO_Port, M2_ENC_B_Pin);
            
            uint8_t idx = ArgonJoint::joint2_Instance()._getEncoderIndex();
            uint8_t enc_idx = (( idx << 2) & 0x0F) + (readA << 1) + readB;
            ArgonJoint::joint2_Instance()._setEncoderIndex(enc_idx);
            
            int32_t encoderCount = ArgonJoint::joint2_Instance().getEncoderCount();
            encoderCount = encoderCount + encoderIndex[enc_idx];
            ArgonJoint::joint2_Instance()._setEncoderCount(encoderCount);
        }
    }
    
    // TIM3
    // Joint 3 - 4
    if( htim->Instance == TIM3 ){
        // Joint 3
        if((htim->Channel == ArgonJointParams::joint3_ic_timer_act_CH_A) || (htim->Channel == ArgonJointParams::joint3_ic_timer_act_CH_B)){
            uint8_t readA = HAL_GPIO_ReadPin(M3_ENC_A_GPIO_Port, M3_ENC_A_Pin);
            uint8_t readB = HAL_GPIO_ReadPin(M3_ENC_B_GPIO_Port, M3_ENC_B_Pin);
            
            uint8_t idx = ArgonJoint::joint3_Instance()._getEncoderIndex();
            uint8_t enc_idx = (( idx << 2) & 0x0F) + (readA << 1) + readB;
            ArgonJoint::joint3_Instance()._setEncoderIndex(enc_idx);
            
            int32_t encoderCount = ArgonJoint::joint3_Instance().getEncoderCount();
            encoderCount = encoderCount + encoderIndex[enc_idx];
            ArgonJoint::joint3_Instance()._setEncoderCount(encoderCount);
        }
        // Joint 4
        if((htim->Channel == ArgonJointParams::joint4_ic_timer_act_CH_A) || (htim->Channel == ArgonJointParams::joint4_ic_timer_act_CH_B)){
            uint8_t readA = HAL_GPIO_ReadPin(M4_ENC_A_GPIO_Port, M4_ENC_A_Pin);
            uint8_t readB = HAL_GPIO_ReadPin(M4_ENC_B_GPIO_Port, M4_ENC_B_Pin);
            
            uint8_t idx = ArgonJoint::joint4_Instance()._getEncoderIndex();
            uint8_t enc_idx = (( idx << 2) & 0x0F) + (readA << 1) + readB;
            ArgonJoint::joint4_Instance()._setEncoderIndex(enc_idx);
            
            int32_t encoderCount = ArgonJoint::joint4_Instance().getEncoderCount();
            encoderCount = encoderCount + encoderIndex[enc_idx];
            ArgonJoint::joint4_Instance()._setEncoderCount(encoderCount);
        }
    }
 
    // TIM4
    // Joint 5 - 6
    if( htim->Instance == TIM4 ){
        // Joint 5
        if((htim->Channel == ArgonJointParams::joint5_ic_timer_act_CH_A) || (htim->Channel == ArgonJointParams::joint5_ic_timer_act_CH_B)){
            uint8_t readA = HAL_GPIO_ReadPin(M5_ENC_A_GPIO_Port, M5_ENC_A_Pin);
            uint8_t readB = HAL_GPIO_ReadPin(M5_ENC_B_GPIO_Port, M5_ENC_B_Pin);
            
            uint8_t idx = ArgonJoint::joint5_Instance()._getEncoderIndex();
            uint8_t enc_idx = (( idx << 2) & 0x0F) + (readA << 1) + readB;
            ArgonJoint::joint5_Instance()._setEncoderIndex(enc_idx);
            
            int32_t encoderCount = ArgonJoint::joint5_Instance().getEncoderCount();
            encoderCount = encoderCount + encoderIndex[enc_idx];
            ArgonJoint::joint5_Instance()._setEncoderCount(encoderCount);
        }
        // Joint 6
        if((htim->Channel == ArgonJointParams::joint6_ic_timer_act_CH_A) || (htim->Channel == ArgonJointParams::joint6_ic_timer_act_CH_B)){
            uint8_t readA = HAL_GPIO_ReadPin(M6_ENC_A_GPIO_Port, M6_ENC_A_Pin);
            uint8_t readB = HAL_GPIO_ReadPin(M6_ENC_B_GPIO_Port, M6_ENC_B_Pin);
            
            uint8_t idx = ArgonJoint::joint6_Instance()._getEncoderIndex();
            uint8_t enc_idx = (( idx << 2) & 0x0F) + (readA << 1) + readB;
            ArgonJoint::joint6_Instance()._setEncoderIndex(enc_idx);
            
            int32_t encoderCount = ArgonJoint::joint6_Instance().getEncoderCount();
            encoderCount = encoderCount + encoderIndex[enc_idx];
            ArgonJoint::joint6_Instance()._setEncoderCount(encoderCount);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM6){
        float rpm_calc_freq = ArgonJointParams::rpm_calc_freq;
        
        //----------------------------------------------------------------------
        // Joint 1
        //----------------------------------------------------------------------
        if(ArgonJoint::joint1_Instance().getAvailable()){
            // Calculate RPM resolution per tick
            float joint1_enc_tick_per_round = ArgonJoint::joint1_Instance().getEncoderTicksPerRound();
            float joint1_encoding_mode = ArgonJoint::joint1_Instance().getEncodingMode();
            float joint1_rpm_res_per_tick = (60.0f * rpm_calc_freq) / (joint1_enc_tick_per_round * joint1_encoding_mode);
            
            if(isnan(joint1_rpm_res_per_tick))
                joint1_rpm_res_per_tick = 0;
            
            // Calculate delta encoder position
            int32_t joint1_encoderCount = ArgonJoint::joint1_Instance().getEncoderCount();
            int32_t joint1_deltaEncoderCount = joint1_encoderCount - ArgonJoint::joint1_Instance()._getPrevEncoderCount();
            
            // Calculate RPM
            float joint1_RPM = joint1_rpm_res_per_tick * ((float)joint1_deltaEncoderCount);
            
            // Store RPM and previous encoder position
            ArgonJoint::joint1_Instance()._setMotorRPM(joint1_RPM);
            ArgonJoint::joint1_Instance()._setPrevEncoderCount(joint1_encoderCount);
            
            // Update Position
            // Encoder tick to Radians
            float joint1_motor_position = ArgonJoint::joint1_Instance().getMotorPosition();       
            float joint1_rev = float(joint1_deltaEncoderCount) / (joint1_enc_tick_per_round * joint1_encoding_mode);
            
            if(isnan(joint1_rev))
                joint1_rev = 0.0f;
            
            joint1_motor_position = joint1_motor_position + REV2RAD * joint1_rev;
            ArgonJoint::joint1_Instance()._setMotorPosition(joint1_motor_position);
        }
        
        //----------------------------------------------------------------------
        // Joint 2
        //----------------------------------------------------------------------
        if(ArgonJoint::joint2_Instance().getAvailable()){
            // Calculate RPM resolution per tick
            float joint2_enc_tick_per_round = ArgonJoint::joint2_Instance().getEncoderTicksPerRound();
            float joint2_encoding_mode = ArgonJoint::joint2_Instance().getEncodingMode();
            float joint2_rpm_res_per_tick = (60.0f * rpm_calc_freq) / (joint2_enc_tick_per_round * joint2_encoding_mode);
            
            if(isnan(joint2_rpm_res_per_tick))
                joint2_rpm_res_per_tick = 0;
            
            // Calculate delta encoder position
            int32_t joint2_encoderCount = ArgonJoint::joint2_Instance().getEncoderCount();
            int32_t joint2_deltaEncoderCount = joint2_encoderCount - ArgonJoint::joint2_Instance()._getPrevEncoderCount();
            
            // Calculate RPM
            float joint2_RPM = joint2_rpm_res_per_tick * ((float)joint2_deltaEncoderCount);
            
            // Store RPM and previous encoder position
            ArgonJoint::joint2_Instance()._setMotorRPM(joint2_RPM);
            ArgonJoint::joint2_Instance()._setPrevEncoderCount(joint2_encoderCount);
            
            // Update Position
            // Encoder tick to Radians
            float joint2_motor_position = ArgonJoint::joint2_Instance().getMotorPosition();       
            float joint2_rev = float(joint2_deltaEncoderCount) / (joint2_enc_tick_per_round * joint2_encoding_mode);
            
            if(isnan(joint2_rev))
                joint2_rev = 0.0f;
            
            joint2_motor_position = joint2_motor_position + REV2RAD * joint2_rev;
            ArgonJoint::joint2_Instance()._setMotorPosition(joint2_motor_position);
        }

        //----------------------------------------------------------------------
        // Joint 3
        //----------------------------------------------------------------------
        if(ArgonJoint::joint3_Instance().getAvailable()){
            // Calculate RPM resolution per tick
            float joint3_enc_tick_per_round = float(ArgonJoint::joint3_Instance().getEncoderTicksPerRound());
            float joint3_encoding_mode = float(ArgonJoint::joint3_Instance().getEncodingMode());
            float joint3_rpm_res_per_tick = (60.0f * rpm_calc_freq) / (joint3_enc_tick_per_round * joint3_encoding_mode);
            
            if(isnan(joint3_rpm_res_per_tick))
                joint3_rpm_res_per_tick = 0;
            
            // Calculate delta encoder position
            int32_t joint3_encoderCount = ArgonJoint::joint3_Instance().getEncoderCount();
            int32_t joint3_deltaEncoderCount = joint3_encoderCount - ArgonJoint::joint3_Instance()._getPrevEncoderCount();
            
            // Calculate RPM
            float joint3_RPM = joint3_rpm_res_per_tick * ((float)joint3_deltaEncoderCount);
            
            // Store RPM and previous encoder position
            ArgonJoint::joint3_Instance()._setMotorRPM(joint3_RPM);
            ArgonJoint::joint3_Instance()._setPrevEncoderCount(joint3_encoderCount);
            
            // Update Position
            // Encoder tick to Radians
            float joint3_motor_position = ArgonJoint::joint3_Instance().getMotorPosition();       
            float joint3_rev = float(joint3_deltaEncoderCount) / (joint3_enc_tick_per_round * joint3_encoding_mode);
            
            if(isnan(joint3_rev))
                joint3_rev = 0.0f;
            
            joint3_motor_position = joint3_motor_position + REV2RAD * joint3_rev;
            ArgonJoint::joint3_Instance()._setMotorPosition(joint3_motor_position);
        }
        
        //----------------------------------------------------------------------
        // Joint 4
        //----------------------------------------------------------------------
        if(ArgonJoint::joint4_Instance().getAvailable()){
            // Calculate RPM resolution per tick
            float joint4_enc_tick_per_round = float(ArgonJoint::joint4_Instance().getEncoderTicksPerRound());
            float joint4_encoding_mode = float(ArgonJoint::joint4_Instance().getEncodingMode());
            float joint4_rpm_res_per_tick = (60.0f * rpm_calc_freq) / (joint4_enc_tick_per_round * joint4_encoding_mode);
            
            if(isnan(joint4_rpm_res_per_tick))
                joint4_rpm_res_per_tick = 0;
            
            // Calculate delta encoder position
            int32_t joint4_encoderCount = ArgonJoint::joint4_Instance().getEncoderCount();
            int32_t joint4_deltaEncoderCount = joint4_encoderCount - ArgonJoint::joint4_Instance()._getPrevEncoderCount();
            
            // Calculate RPM
            float joint4_RPM = joint4_rpm_res_per_tick * ((float)joint4_deltaEncoderCount);
            
            // Store RPM and previous encoder position
            ArgonJoint::joint4_Instance()._setMotorRPM(joint4_RPM);
            ArgonJoint::joint4_Instance()._setPrevEncoderCount(joint4_encoderCount);
            
            // Update Position
            // Encoder tick to Radians
            float joint4_motor_position = ArgonJoint::joint4_Instance().getMotorPosition();       
            float joint4_rev = float(joint4_deltaEncoderCount) / (joint4_enc_tick_per_round * joint4_encoding_mode);
            
            if(isnan(joint4_rev))
                joint4_rev = 0.0f;
            
            joint4_motor_position = joint4_motor_position + REV2RAD * joint4_rev;
            ArgonJoint::joint4_Instance()._setMotorPosition(joint4_motor_position);
        }
        
        //----------------------------------------------------------------------
        // Joint 5
        //----------------------------------------------------------------------
        if(ArgonJoint::joint5_Instance().getAvailable()){
            // Calculate RPM resolution per tick
            float joint5_enc_tick_per_round = float(ArgonJoint::joint5_Instance().getEncoderTicksPerRound());
            float joint5_encoding_mode = float(ArgonJoint::joint5_Instance().getEncodingMode());
            float joint5_rpm_res_per_tick = (60.0f * rpm_calc_freq) / (joint5_enc_tick_per_round * joint5_encoding_mode);
            
            if(isnan(joint5_rpm_res_per_tick))
                joint5_rpm_res_per_tick = 0;
            
            // Calculate delta encoder position
            int32_t joint5_encoderCount = ArgonJoint::joint5_Instance().getEncoderCount();
            int32_t joint5_deltaEncoderCount = joint5_encoderCount - ArgonJoint::joint5_Instance()._getPrevEncoderCount();
            
            // Calculate RPM
            float joint5_RPM = joint5_rpm_res_per_tick * ((float)joint5_deltaEncoderCount);
            
            // Store RPM and previous encoder position
            ArgonJoint::joint5_Instance()._setMotorRPM(joint5_RPM);
            ArgonJoint::joint5_Instance()._setPrevEncoderCount(joint5_encoderCount);
            
            // Update Position
            // Encoder tick to Radians
            float joint5_motor_position = ArgonJoint::joint5_Instance().getMotorPosition();       
            float joint5_rev = float(joint5_deltaEncoderCount) / (joint5_enc_tick_per_round * joint5_encoding_mode);
            
            if(isnan(joint5_rev))
                joint5_rev = 0.0f;
            
            joint5_motor_position = joint5_motor_position + REV2RAD * joint5_rev;
            ArgonJoint::joint5_Instance()._setMotorPosition(joint5_motor_position);
        }
        
        //----------------------------------------------------------------------
        // Joint 6
        //----------------------------------------------------------------------
        if(ArgonJoint::joint6_Instance().getAvailable()){
            // Calculate RPM resolution per tick
            float joint6_enc_tick_per_round = float(ArgonJoint::joint6_Instance().getEncoderTicksPerRound());
            float joint6_encoding_mode = float(ArgonJoint::joint6_Instance().getEncodingMode());
            float joint6_rpm_res_per_tick = (60.0f * rpm_calc_freq) / (joint6_enc_tick_per_round * joint6_encoding_mode);
            
            if(isnan(joint6_rpm_res_per_tick))
                joint6_rpm_res_per_tick = 0;
            
            // Calculate delta encoder position
            int32_t joint6_encoderCount = ArgonJoint::joint6_Instance().getEncoderCount();
            int32_t joint6_deltaEncoderCount = joint6_encoderCount - ArgonJoint::joint6_Instance()._getPrevEncoderCount();
            
            // Calculate RPM
            float joint6_RPM = joint6_rpm_res_per_tick * ((float)joint6_deltaEncoderCount);
            
            // Store RPM and previous encoder position
            ArgonJoint::joint6_Instance()._setMotorRPM(joint6_RPM);
            ArgonJoint::joint6_Instance()._setPrevEncoderCount(joint6_encoderCount);
            
            // Update Position
            // Encoder tick to Radians
            float joint6_motor_position = ArgonJoint::joint6_Instance().getMotorPosition();       
            float joint6_rev = float(joint6_deltaEncoderCount) / (joint6_enc_tick_per_round * joint6_encoding_mode);
            
            if(isnan(joint6_rev))
                joint6_rev = 0.0f;
            
            joint6_motor_position = joint6_motor_position + REV2RAD * joint6_rev;
            ArgonJoint::joint6_Instance()._setMotorPosition(joint6_motor_position);
        }
    }
}
