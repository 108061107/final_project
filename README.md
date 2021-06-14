# final_project
*****Designed tasks: (1)follow a line (2)use apriltag to check bbcar's location (3)prevent bbcar from hitting a obstacle 
(4)after avoiding the obstacle, steer bbcar to go to a destination by using ping to detect the distance between bbcar and the destination 
(5)also send information with XBee at the start and end of each sub-task.*****\
\
使用hw4(line following)的方法讓車子沿著直線行駛，當偵測到直線時，利用xbee回傳訊息給pc端，告知開始沿著直線前進，沿直線行駛的方法為在openmv的main.py中增加判斷線段的條件，
進而將環境中多餘的線段消除，如此範圍內會只剩下需要被偵測的那條直線，讓車子沿著這條直線行走，當線段結束，便讓車子停下來不再前進，並利用xbee回傳給pc告知結束follow line的任務。\
設置一個障礙物在線段結束的地方，並在障礙物測後方顯示apriltag，利用hw4(position calibration)，使用openmv偵測apriltag，偵測到apriltag時，利用xbee回傳pc告知已偵測到apriltag，
記錄其偵測到的各項距離、角度，將需要的資料擷取下來並回傳給mbed，將資料進行運算過後得到bbcar的位置和需要位移的距離，利用xbee回傳車子的位置到pc，
然後依據車子在apriltag的右側或左側將車子移動到正面對apriltag，同時也避開前方設置的障礙物，利用xbee回傳pc告知結束位置校正。\
避開障礙物後，利用xbee回傳pc告知開始前往目的地，並使車子開向前方的apriltag，使用ping來偵測車子與目的地之間的距離，當車子與目的地之間的距離小於30公分後讓車子停下來，
利用xbee回傳pc告知已到達目的地。\
\
*****執行結果:*****\
