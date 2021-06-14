# final_project
*****Designed tasks: (1)follow a line (2)use apriltag to check bbcar's location (3)facing directly to the apriltag and also prevent bbcar from hitting a obstacle 
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
follow line:\
![line1](https://user-images.githubusercontent.com/79581724/121883139-f6ad7d80-cd43-11eb-86d9-37f7eb4386ad.jpg)\
![line2](https://user-images.githubusercontent.com/79581724/121883153-fad99b00-cd43-11eb-9c61-c1ed2be1b409.jpg)\
![line3](https://user-images.githubusercontent.com/79581724/121883161-fca35e80-cd43-11eb-91be-1aa9a8d561a7.jpg)\
prevent bbcar from hitting a obstacle:\
![avoiding](https://user-images.githubusercontent.com/79581724/121883232-1349b580-cd44-11eb-86bc-c091e3544d22.jpg)\
![avoiding2](https://user-images.githubusercontent.com/79581724/121883245-1644a600-cd44-11eb-82d6-3963b55e26f3.jpg)\
facing directly to the apriltag:\
![facing](https://user-images.githubusercontent.com/79581724/121883258-19d82d00-cd44-11eb-809c-e57e533b9ebc.jpg)\
steer bbcar to go to a destination:\
![go to destination](https://user-images.githubusercontent.com/79581724/121883396-468c4480-cd44-11eb-8edb-27e0d54482ae.jpg)\
arrived:\
![destination arrived](https://user-images.githubusercontent.com/79581724/121883408-48ee9e80-cd44-11eb-9789-39d9d183ef41.jpg)\
send information with XBee at the start and end of each sub-task:\
![xbee回傳結果](https://user-images.githubusercontent.com/79581724/121883786-c0243280-cd44-11eb-99bf-620e2700f3bd.png)
