
//************************************************************
//void ultrasonicDetection() //測量3個角度(前.左.右)
//{
//    distanceForward(); // 讀取前方距離
//
//    if(Fspeedd < 10 && Fspeedd > 2) // 假如前方距離小於10公分
//    {
//        brake(); // 清除輸出資料
//        moveBack(200); // 後退 0.2秒
//    }
//    if(Fspeedd < 25 && Fspeedd > 2) // 假如前方距離小於25公分
//    {
//        brake(100); // 清除輸出資料 
//        distanceLeft(); // 讀取左方距離
//        delay(100); 
//        distanceRight(); // 讀取右方距離 
//        delay(100); // 等待伺服馬達穩定 
//
//        if(Lspeedd > Rspeedd) move_direction = go_left; //向左走
//        if(Lspeedd <= Rspeedd) move_direction = go_right; //向右走
//        if(Lspeedd < 15 && Rspeedd < 15) move_direction = go_back; //向後走 
//    }
//    else move_direction = go_forward; //向前走 
//}
//
//void distanceForward() // 量出前方距離 
//{
//    digitalWrite(ul_trig, LOW); // 讓超聲波發射低電壓2μs
//    delayMicroseconds(2);
//    digitalWrite(ul_trig, HIGH); // 讓超聲波發射高電壓10μs，這裡至少是10μs
//    delayMicroseconds(10);
//    digitalWrite(ul_trig, LOW);
//    int Fdistance = pulseIn(ul_echo, HIGH);
//    Fdistance= Fdistance/58; 
//    Serial.print("F distance:");
//    Serial.println(Fdistance);
//    delay(50);
//    Fspeedd = Fdistance;
//}
//
//void distanceLeft() // 量出左邊距離 
//{
//    moveLeft(1000);
//    digitalWrite(ul_trig, LOW); // 讓超聲波發射低電壓2μs
//    delayMicroseconds(2);
//    digitalWrite(ul_trig, HIGH); // 讓超聲波發射高電壓10μs，這裡至少是10μs
//    delayMicroseconds(10);
//    digitalWrite(ul_trig, LOW); // 維持超聲波發射低電壓
//    float Ldistance = pulseIn(ul_echo, HIGH); // 讀差相差時間
//    Ldistance= Ldistance/58; // 將時間轉為距離距离（單位：公分）
//    Serial.print("L distance:"); //輸出距離（單位：公分）
//    Serial.println(Ldistance); //顯示距離
//    Lspeedd = Ldistance; // 將距離 讀入Lspeedd(左速)
//    moveRight(1000);
//    brake(500);
//}
//
//void distanceRight() // 量出右邊距離 
//{
//    moveRight(1000);
//    digitalWrite(ul_trig, LOW); // 讓超聲波發射低電壓2μs
//    delayMicroseconds(2);
//    digitalWrite(ul_trig, HIGH); // 讓超聲波發射高電壓10μs，這裡至少是10μs
//    delayMicroseconds(10);
//    digitalWrite(ul_trig, LOW); // 維持超聲波發射低電壓
//    float Rdistance = pulseIn(ul_echo, HIGH); // 讀差相差時間
//    Rdistance= Rdistance/58; // 將時間轉為距離距离（單位：公分）
//    Serial.print("R distance:"); //輸出距離（單位：公分）
//    Serial.println(Rdistance); //顯示距離
//    Rspeedd = Rdistance; // 將距離 讀入Rspeedd(右速)
//    moveLeft(1000);
//    brake(500);
//} 
