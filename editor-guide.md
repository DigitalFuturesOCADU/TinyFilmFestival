# LED Matrix Editor Guide

The Arduino LED Matrix Editor (https://ledmatrix-editor.arduino.cc/) provides a visual interface for creating LED matrix animations. It allows you to
- Create the animations by painting/erasing pixels frame by frame
- Copying Frames to allow easy transtions
- Moving the pixels as a group within a frame
- Setting the display time for each frame

## Interface

![LED Matrix Editor](images/matrixEditor.png)

## Project Controls
- Start/Stop preview: spacebar
- Start/Stop preview with loop: ⇧ + spacebar
- Upload project: Ctrl + U
- Save project: Ctrl + S
- Export code: Ctrl + E

## Canvas Controls
- Brush: B
- Eraser: E
- Clear frame: ⌘ + ⌫
- Move pixels: ⇧ + arrow keys
- Move pixels with wrap: ⇧ + ⌘ + arrow keys

## Timeline Controls
- New frame: Ctrl + N
- Duplicate frame: Ctrl + D
- Delete frame: Ctrl + ⌫
- Delete all frames: Ctrl + ⇧ + ⌫
- Move between frames: arrow keys

## File Types : Saving Your Working File Vs Exporting Your Animation

When using the Matrix Editor it is important to remember that it is a web-based tool, so your work is not autmatically saved.

- ![download mpj](images/mpjDownload.png) Save the current working File as a downloaded **.mpj**
- ![upload mpj](images/mpjUpload.png) Restore a previous Session by uploading an **.mpj** file
- ![download h](images/hDownload.png) Export the animation as a **.h** file that can be read by Arduino


![down controls](images/downloadControls.png)


## Playing / Controlling your Animation on your Arduino
There are a few simple steps required to go from the animation you see in the Editor, to playing it on the Arduino Matrix
1. Once you are happy with your animation, press the ![download h](images/hDownload.png) button to download your animation as a **.h** code file. This step takes the entire frame sequence and converts it into code that can be understood by arduino. When you press the button, it will bring up a dialog box. **Choose a name for the file that describes the animation**
- **Do not include any spaces in the file name**

![steps](images/downloadSteps.png)

2. Locate the Folder that contains your Arduino File
3. Copy the **.h** file you just downloaded into the same folder as your main Arduino File
4. Change the name of the #include to match the name of your file
5. Change the name of the variable referenced by the Animation variable to match your file

![variables](images/variableNames.png)

### Once you have completed 1 - 5 you can use all function of TinyFilmFestival to control your animaation