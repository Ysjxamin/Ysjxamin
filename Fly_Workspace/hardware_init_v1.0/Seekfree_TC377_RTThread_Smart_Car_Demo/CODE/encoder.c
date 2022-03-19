#include "encoder.h"

#define ENCODER1_GPT		    GPT12_T2
#define ENCODER1_A_PLUS			GPT12_T2INB_P33_7
#define ENCODER1_B_DIR			GPT12_T2EUDB_P33_6

#define ENCODER2_GPT            GPT12_T4
#define ENCODER2_A_PLUS         GPT12_T4INA_P02_8
#define ENCODER2_B_DIR          GPT12_T4EUDA_P00_9

#define ENCODER3_GPT            GPT12_T5
#define ENCODER3_A_PLUS         GPT12_T5INB_P10_3
#define ENCODER3_B_DIR          GPT12_T5EUDB_P10_1

#define ENCODER4_GPT            GPT12_T6
#define ENCODER4_A_PLUS         GPT12_T6INA_P20_3
#define ENCODER4_B_DIR          GPT12_T6EUDA_P20_0

int16 encoder1;
int16 encoder2;
int16 encoder3;
int16 encoder4;

void encoder_init(void)
{
    gpt12_init(ENCODER1_GPT, ENCODER1_A_PLUS, ENCODER1_B_DIR);
    gpt12_init(ENCODER2_GPT, ENCODER2_A_PLUS, ENCODER2_B_DIR);
    gpt12_init(ENCODER3_GPT, ENCODER3_A_PLUS, ENCODER3_B_DIR);
    gpt12_init(ENCODER4_GPT, ENCODER4_A_PLUS, ENCODER4_B_DIR);
}


void encoder_get(void)
{
    encoder1 = gpt12_get(ENCODER1_GPT);
    encoder2 = gpt12_get(ENCODER2_GPT);
    encoder3 = gpt12_get(ENCODER3_GPT);
    encoder4 = gpt12_get(ENCODER4_GPT);

    gpt12_clear(ENCODER1_GPT);
    gpt12_clear(ENCODER2_GPT);
    gpt12_clear(ENCODER3_GPT);
    gpt12_clear(ENCODER4_GPT);
}
