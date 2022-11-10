# DIY RC Airplane

*Projects hướng dẫn DIY một chiếc máy bay hoàn chỉnh từ A-Z*

![img.png](img.png)

https://www.youtube.com/shorts/XCcPUDrcOQ8

# 1. Nguyên lý và thiết bị

Để điều khiển máy bay, bộ điều khiển cần 2 thiết bị gồm : 
- Transmitter (TX) : Bộ phát sóng, là thiết bị sử dụng điều khiển máy bay.
- Receiver (RX) : Bộ thu sóng đặt trên máy bay. 

![alt text](img/tx_rx_futaba.png)

Bài viết này mình sẽ hướng dẫn tạo bộ Transmitter và Receiver với Arduino.

## 1.1 Nguyên lý 

![alt text](./img/txrx.png)

- **TX** : Gồm 2 Joy sticks (Núm điều khiển), tín hiệu sẽ được truyền từ Joy Sticks tới Arduino, từ Arduino sẽ truyền thông tin qua mạch Wifi.
- **RX** : Nhận sóng truyền tới, xử lý tại mạch Arduino Nano, sau đó truyền tín hiệu tới Servo, Motor

## 2.2 Thiết bị

**Thiết bị cần cho Transmitter**

![alt text](img/tx_devices.png)

**Thiết bị cần cho Receiver**

![alt text](img/rx_devices.png)

**Thiết bị điện cho máy bay**

![alt text](img/airplane_devices.png)


# 2. Nối mạch điện 

## 2.1 Transmitter

*Lưu ý*:
- Mạch wifi sử dụng nguồn 3.3V. Chú ý sử dụng đúng nguồn 3.3V
- Joy stick sử dụng nguồn 5V. 
- Mạch Arduino có thể dùng nguồn 3.3V lấy từ cục xạc dự phòng

![alt text](img/tx_map.png)

## 2.2 Receiver
![alt text](img/rx_map.png)

# 3. Lập trình
Tham khảo bài viết tại đây để biết cách nạp chương trình cho mạch

http://arduino.vn/bai-viet/402-huong-dan-nap-chuong-trinh-don-gian-cho-arduino-uno-r3

## 3.1 Lập trình cho TX
> TODO : Nội dung sẽ được update sớm

**Joy Stick**
*Lưu ý với Joy Stick*
- Joy Stick truyền tín hiệu Analog, vì vậy cần sử dụng Port A0 - A5 trên mạch Arduino.
- 1 Joy Stick gửi 2 tín hiệu tương ứng trục X và Y, với Joy Stick 1 ta dùng cổng A0 - A1, Joy Stick 2 dùng A3 và A4
- Joy Stick trả về giá trị từ 0 - 1024, khi ở vị trí thấp nhất, giá trị ta nhận được là 0 và khi ở vị trí cao nhất, ta nhận được giá trị 1024


```
// Định nghĩa port sử dụng nhận tín hiệu từ Joy Stick
// Joy Stick 1
#define STICK1_X  A0 // Arduino pin connected to VRX pin
#define STICK1_Y  A1 // Arduino pin connected to VRY pin
// Joy Stick 2
#define STICK2_X  A2 // Arduino pin connected to VRX pin
#define STICK2_Y  A3 // Arduino pin connected to VRY pin

// Định nghĩa Joy Stick lưu trữ 2 trục X và Y
struct JoyStick{
  byte x;
  byte y;
};


// Function nhận tín hiệu từ Joy Stick, lưu vào biến stick
JoyStick read_joy_stick(int stick_num){

  struct JoyStick stick;

  switch (stick_num){
    case 1:
      stick.x =  map(analogRead(STICK1_X), 0, 1023, 0, 255);
      stick.y =  map(analogRead(STICK1_Y), 0, 1023, 0, 255);
      break;
    case 2:
      stick.x =  map(analogRead(STICK2_X), 0, 1023, 0, 255);
      stick.y =  map(analogRead(STICK2_Y), 0, 1023, 0, 255);
      break;
  }
  return stick;
}
```
## 3.2 Lập trình cho RX

# 4. Tạo mô hình máy bay
> TODO : Nội dung sẽ được update sớm
