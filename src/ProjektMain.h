/*
    G��wny frame w kt�rym s� prze��czane kolejne panele
*/

#ifndef PROJEKTMAIN_H
#define PROJEKTMAIN_H

#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>

#include "PanelGry.h"
#include "PanelGlowny.h"
#include "PanelOpcji.h"
#include "PanelPunkty.h"
#include "BestScores.h"

#include "stdio.h"

#define STATE_MAIN 0
#define STATE_OPTIONS 1
#define STATE_SCORE 2
#define STATE_GAME 3


class ProjektFrame: public wxFrame{
    public:

        ProjektFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ProjektFrame();        
        
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void Quit();
        void setState(char state);
		void setGamePanel(GamePanel * panel);
		bool gameStarted(){return _gamePanel != NULL;}
		void gameFinished();
                
        static ProjektFrame * FRAME;
        
        enum{
    		ID_PANEL1 = 1,
            idMenuQuit = 2,
            idMenuAbout = 3,
            ID_STATUSBAR1 = 4,
    		ID_PANEL_GRY = 5,
    		ID_PANEL_GLOWNY = 6,
    		ID_PANEL_PUNKTY = 7,
    		ID_PANEL_OPCJI = 8
        };
               
    private:
                      
		DECLARE_EVENT_TABLE();
		
        wxStatusBar* StatusBar1;        
        wxPanel * _currentPanel;
        
        GamePanel * _gamePanel;
        OptionsPanel * _optionPanel;
        ScorePanel * _scorePanel;
        MainPanel * _mainPanel;
        
        BestScores* _scores;
};

#endif // PROJEKTMAIN_H
