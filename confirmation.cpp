#include "include/confirmation.hpp"
#include "include/camera.hpp"
#include <opencv/cv.h>

namespace iwb {

    Confirmation* Confirmation::instance = NULL;

    bool Confirmation::create(Presentation* prs, Handler* hndl) {
        if (instance == NULL) {
            instance = new Confirmation(prs, hndl);
            return true;
        }
        return false;
    }

    void Confirmation::hide() {
        delete(instance);
        instance = NULL;
    }
    
    Confirmation::Confirmation(Presentation* prs, Handler* hndl) {
        this->prs = prs;
        this->hndl = hndl;

        initialize();
    }

    Confirmation::~Confirmation() {
        freeButtons();
    }

    void Confirmation::freeButtons() {
        deleteButton(yesButton);
        deleteButton(noButton);
    }

    void Confirmation::deleteButton(Touchable* button) {
        prs->removeComponent(button);
        delete(button);
    }
		void testcb2() {
			printf("TOUCHED!\n");
		};

    void Confirmation::initialize() {
        CvPoint upperLeft = cvPoint(850, 0);
        CvPoint lowerRight = cvPoint(1000, 200);

        int confirmWidth = lowerRight.x - upperLeft.x;
        int confirmHeight = lowerRight.y - upperLeft.y;

        printf("confirmWidth: %d, confirmHeight: %d", confirmWidth, confirmHeight);

        CvPoint yesUL;
        CvPoint yesBR;
        CvPoint noUL;
        CvPoint noBR;

        yesUL = cvPoint(
                upperLeft.x + round(0.00 * confirmWidth),
                upperLeft.y + round(0.25 * confirmHeight)
                );
        yesBR = cvPoint(
                upperLeft.x + round(0.45 * confirmWidth),
                upperLeft.y + round(0.75 * confirmHeight)
                );

        noUL = cvPoint(
                upperLeft.x + round(0.50 * confirmWidth),
                upperLeft.y + round(0.25 * confirmHeight)
                );
        noBR = cvPoint(
                upperLeft.x + round(0.95 * confirmWidth),
                upperLeft.y + round(0.75 * confirmHeight)
                );

        char* paths[2] = {"res/yes.jpg", "res/no.jpg"};

        yesButton = new Touchable(paths[0], this->prs, this->hndl, yesUL, yesBR, &testcb2);

        noButton= new Touchable(paths[1], this->prs, this->hndl, noUL, noBR, &testcb2);
    }
}
