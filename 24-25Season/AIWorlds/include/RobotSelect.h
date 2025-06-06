#pragma once

#define Backpack_Red 0
#define Backpack_Blue 1
#define Dora 2
#define Dev_Backpack_Master 3
#define Dev_Mecc_Worker 4

#define CURRENT_ROBOT Dora

#if CURRENT_ROBOT == Backpack_Red
#warning "Using Backpack Red robot configuration"
#elif CURRENT_ROBOT == Backpack_Blue
#warning "Using Backpack Blue robot configuration"
#elif CURRENT_ROBOT == Dora
#warning "Using Dora robot configuration"
#elif CURRENT_ROBOT == Dev_Backpack_Master
#warning "Using Dev Backpack Master robot configuration"
#elif CURRENT_ROBOT == Dev_Mecc_Worker
#warning "Using Dev Mecc Worker robot configuration"
#endif