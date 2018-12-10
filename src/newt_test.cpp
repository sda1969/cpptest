/*
 * newt_test.cpp
 *
 *  Created on: 07 апр. 2017 г.
 *      Author: dmitry
 */

#include <iostream>
#include <newt.h>
#include <stdlib.h>
#include <string.h>

namespace newt_test {

/* newt cleanup stuff */
void cleanupNewt() {

    newtFinished();

}

/* newt initialization stuff with background title */
void initNewt(unsigned int y, const char* pTitle) {

    int uiWidth = 0, uiHeight = 0;
    newtGetScreenSize(&uiWidth, &uiHeight);

    newtInit();
    newtCls();
    newtDrawRootText((uiWidth-strlen(pTitle))/2, y, pTitle);
    newtPushHelpLine(" < Press ok button to see your greetings > ");

}

/* draw centered window with components and specified title */
void drawWindow(unsigned int uiW, unsigned int uiH, char* pTitle, char* pEntryText) {

    newtComponent form, label, entry, button;
    char* pEntry;

    newtCenteredWindow(uiW, uiH, pTitle);
    label = newtLabel(2, uiH/4, "Geek's Name");
    entry = newtEntry(uiW/2, uiH/4, "RichNusGeeks", 12, \
                      (const char**) &pEntry, 0);
    button = newtButton((uiW-6)/2, 2*uiH/3, "Ok");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label, entry, button, NULL);
    newtRunForm(form);

    strncpy(pEntryText, pEntry, 12);
    newtFormDestroy(form);

}

/* draw a centered message box */
void messageBox(unsigned int uiW, unsigned int uiH, const char* pMessage) {

    newtComponent form, label, button;

    newtCenteredWindow(uiW, uiH, "Message Box");
    newtPopHelpLine();
    newtPushHelpLine(" < Press ok button to return > ");

    label = newtLabel((uiW-strlen(pMessage))/2, uiH/4, pMessage);
    button = newtButton((uiW-6)/2, 2*uiH/3, "Ok");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label, button, NULL);
    newtRunForm(form);

    newtFormDestroy(form);

}

static void newt_01(){
    /* required variables and string */
       int uiRows, uiCols;
       const char pcText[] = "Welcome to Newt and FLOSS !!!";

       /* initialization stuff */
       newtInit();
       newtCls();

       /* determine current terminal window size */
       uiRows = uiCols = 0;
       newtGetScreenSize(&uiCols, &uiRows);

       /* draw standard help and string on root window */
       newtPushHelpLine(NULL);
       newtDrawRootText((uiCols-strlen(pcText))/2, uiRows/2, pcText);

       /* cleanup after getting a keystroke */
       newtWaitForKey();
       newtFinished();

}

static void newt_02(){
    /* constant and variable data required */
    const char pBackTitle[] = "-----Newt Greeter for FOSS Hackers-----";
    char pName[20], pMessage[40];

    /* initialize newt stuff */
    initNewt(1, pBackTitle);

    drawWindow(30, 10, "Greeter !!!", pName);
    snprintf(pMessage, 39, "FOSS loves geeks like %s \\m/", pName);
    messageBox(40, 10, pMessage);

    /* cleanup newt library */
    cleanupNewt();
}

void newt_test_run() {

//    newt_01();
    newt_02();


}

}
