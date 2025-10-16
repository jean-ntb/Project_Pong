#include "Config.h"

// Dans ton fichier .h
enum etat_Button {
    BTN_PRESSED,
    BTN_RELEASED
};
struct Button_Data{
    int pin;
    etat_Button etat_actuel;
    etat_Button etat_precedent; 
    bool relache_detect;
    bool appuie_detect;
};

void button_Init(Button_Data* btn);
void button_Update(Button_Data* btn);
bool button_EstAppuye(Button_Data* btn);
bool button_AppuiDetecte(Button_Data* btn);
bool button_RelacheDetecte(Button_Data* btn);  
