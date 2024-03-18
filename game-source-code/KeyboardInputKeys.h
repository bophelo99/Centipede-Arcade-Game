#ifndef KEYBOARDINPUTKEYS_H
#define KEYBOARDINPUTKEYS_H

/** \struct KeyboardInputKeys
 *  \brief This is a Interface Class containing pure virtual functions that
 *         will be overridden by derived classes.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

struct KeyboardInputKeys
{
   bool isLeftButtonPressed = false;
   bool isRightButtonPressed = false;
   bool isUpButtonPressed = false;
   bool isDownButtonPressed = false;
   bool isSpaceButtonPressed = false;
   bool isEscapeButtonPressed = false;
};

#endif // KEYBOARDINPUTKEYS_H
