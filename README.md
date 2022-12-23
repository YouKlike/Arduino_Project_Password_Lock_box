複合型密碼鎖
===
## Overview
*   [專題動機](#motivation)
*   [專題目的](#purpose)
*   [模組介紹](#equipment)
    *   [Fingerprint Module (AS608)](#fingerprint)
    *   [4X4 keypads](#keypads)
    *   [LCD 1602](#LCD)
    *   [LED RGB 140C05](#LED)
    *   [Touch Sensor TTP223](#touchsensor)
    *   [Servo SG90](#servo)
*   [流程圖](#flow_chart)
*   [電路圖](#circuit_diagram)
*   [程式解析](#program_analysis)
*   [成員設置](#groupsetting)
    *   [蔡秉岑](#YouKlike)
    *   [陳衍浩](#Travis)
    *   [陳則瑜](#Jerry)
    *   [張詠喻](#YekNiT)
*   [參考資料](#references)
---

## 專題動機<span id="motivation"></span>
本次專題我們設計了一組複合密碼鎖，此密碼鎖能夠透過輸入密碼與指紋辨識的方式進行保險箱的解鎖，也能夠將輸入的密碼與保險箱解鎖狀態顯示於顯示器上。

---

## 專題目的<span id="purpose"></span> 
挖坑給自己跳 by.YouKlike
伺服馬達怎麼又壞掉 by.Travis.C
為什麼字對不齊 by.YekNiT


---
## 模組介紹<span id="equipment"></span>
### Fingerprint Module (AS608)<span id="fingerprint"></span>
![unsplash 圖片](https://cdn.store-assets.com/s/236824/i/11815788.jpeg?width=256)

利用指紋演算法從獲取的指紋圖像中提取特徵，能夠偵測指紋並記錄，將使用者的指紋儲存以供後續執行程式時進行輸入、判別。

    使用Adafruit_Fingerprint函式庫。
### 4X4 keypads<span id="keypads"></span>
![unsplash 圖片](https://hackster.imgix.net/uploads/attachments/1361245/download_EX5bsc1JDI.jfif?auto=compress%2Cformat&w=680&h=510&fit=max)

共有16個按鍵，有八個腳位(四行四列)。 
本次專題用來輸入密碼與切換執行程式，可更改密碼與加入指紋。

    使用Adafruit Keypad函式庫。
### LCD 1602<span id="LCD"></span>
<img decoding="async" src="https://www.taiwansensor.com.tw/wp-content/uploads/2018/03/61tr-X4R-L._SL1100_.jpg" width="40%">

利用16*2的液晶顯示器來顯示目前程式執行狀態與密碼輸入提示，讓使用者能得知目前的解鎖狀況。

    使用LiquidCrystal函式庫。

### LED RGB 140C05<span id="LED"></span>
<img decoding="async" src="https://www.taiwansensor.com.tw/wp-content/uploads/2018/03/LCR-002004.jpg" width="40%">

用於提示目前程式運行狀態，如密碼輸入是否正確等

### Touch Sensor TTP223<span id="touchsensor"></span>
<img decoding="async" src="https://shop.mirotek.com.tw/wp-content/uploads/2021/03/400078-1.jpg" width="40%">

功能如按鈕，觸碰後關上閘門

### Servo SG90<span id="servo"></span>
<img decoding="async" src="https://www.diyelectronics.co.za/store/3045/towerpro-micro-9-gram-hobby-servo-sg90.jpg" width="40%">

功能如按鈕，觸碰後關上閘門

---

## 流程圖<span id="flow_chart"></span>
![](https://i.imgur.com/fhrPdDY.png)

---

## 電路圖<span id="circuit_diagram"></span>
![](https://i.imgur.com/gxATDZk.png)

---

## 程式解析<span id="program_analysis"></span>

---

## 成員設置<span id="groupsetting"></span>

### 蔡秉岑<span id="YouKlike"></span>

### 陳衍浩<span id="Travis"></span>

### 陳則瑜<span id="Jerry"></span>

### 張詠喻<span id="YekNiT"></span>
---

