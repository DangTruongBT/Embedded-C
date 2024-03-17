# Embedded-C
<details><summary>LESSON 1: GPIO</summary>
<p>
  
  ## LESSON 1: GPIO
  
  ### Để cấu hình cho ngoại vi GPIO ta thực hiện các bước sau:
![Screenshot 2024-03-17 104919](https://github.com/DangTruongBT/Embedded-C/assets/103482832/6f377fe6-7e22-4958-bbed-43e8a3c3cb74)
  #### Cấp xung clock cho ngoại vi:
  Ta nhìn vào diagram của vi điều khiển sửử dụng các API được cung cấp sẵn cho từng Bus. Các ngoại vi trên Bus được cấp xung thông qua việc truyền các tham số vào API này.
  
![Screenshot 2024-03-17 111122](https://github.com/DangTruongBT/Embedded-C/assets/103482832/3e3eacc9-e1a9-42e4-9566-599bf3d32e34)


- Ví dụ: nếu bạn muốn sử dụng chân PB2 thì bạn phải cấp xung cho GPIO, muốn cấp xung cho GPIO thì phải cấp xung cho bus mà GPIO treo lên là APB2.
- Trong VDK STM32 thì thanh ghi dùng để cấp clock là thanh ghi RCC
- Cú pháp để cấp/không cấp clock cho một ngoại vi là:
  
  **RCC_(Tên Bus)PerighClockCmd(ngoại vi cần cấu hình, Trạng thái);**

   - Tên bus mình muốn cấp clock (AHB, APB1, APB2)
   - Ngoại vi cần cấu hình: ví dụ GPIOC, GPIOB...
   - Trạng thái:  cho cấp phép/không cấp (ENABLE/DISABLE)
  
     *Ví dụ: Chúng ta cần cấp xung cho thanh ghi GPIOB, ta thiết lập như sau:*
     ```c
       void RCC_Config() {
       RCC_APB2PeriphClockCmd(RCC_APB2Phriph_GPIOB, ENABLE);
        }
   
    #### Sau khi ngoại vi được cấp clock, chúng ta có thể thiết lập các cấu hình cho ngoại vi đó.

     - Sau khi được cấp xung, ta sử dụng hàm GPIO_Init(GPIOx, &GPIO_InitStruct) để cấu hình
     - 
       Trong đó:

        GPIOx : GPIO cần cấu hình

        GPIO_InitStruct : Biến chứa các thông tin để cấu hình cho GPIO có kiểu dữ liệu GPIO_InitTypeDef
       
        GPIO_InitTypeDef là 1 kiểu struct chứa các trường sau:

       ```c
        GPIO_Pin        : Chọn Pin đang cần để cấu hình
    
        GPIO_Mode       : Chọn chế độ cho Pin
    
        GPIO_Speed      : Chọn tốc độ phản hồi

    Nếu cấu hình Pin là đầu vào, ta có thể chọn:

       
       Input Pull Down   : Thiết lập đầu vào và mức logic ở mức 0 (0V) khi không tác động (dùng điện trở kéo xuống )
       Input Pull Up     : Thiết lập đầu vào và mức logic ở mức 1 (3,3V) khi không tác động (dùng điện trở kéo lên nguồn)
       Input Floating    :
  
    Nếu cấu hình Pin là đầu ra, ta thường sử dụng:

       Output Push Pull  : Cho phép tùy chỉnh tín hiệu ở 2 mức logic 0 (0V) và 1 (3,3V)'
       Output Open Drain :
  
   Ví dụ: Ta cần cấu hình cho led PC13 và nút bấm PB4
  
     ```c
       void GPIO_Config(){
      	 GPIO_InitTypeDef GPIO_InitStructure;
	
      	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13  ;
	       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
     	   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
      	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4  ;
      	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
     	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	       GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
     
Sau khi thiết lập xong, ngoại vi đã có thể sử dụng, tùy thuộc vào mục đích, yêu cầu bài toán để sử dụng các Pin với các hàm tương ứng.
 - Đọc giá trị đầu vào tại 1 Pin (1 bit) của thanh ghi
   
        uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
   
 - Đọc giá trị đầu vào của cả 1 thanh ghi

       uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);

 - Đọc giá trị đầu ra tại 1 Pin (1 bit) của thanh ghi

       uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
   
 - Đọc giá trị đầu ra của cả 1 thanh ghi

       uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
   
 - Thay đổi giá trị lên mức logic 1 của 1 Pin trên thanh ghi

       void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
   
 - Thay đổi giá trị về mức logic 0 của 1 Pin trên thanh ghi

       void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

 - Thay đổi giá trị của 1 Pin trên thanh ghi

       void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

- Thay đổi giá trị của 1 Pin hoặc nhiều Pin trên thanh ghi

       void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);

        

</p>


</details>
   
<details><summary>LESSON 2: NGẮT&TIMER</summary>
<p>
	
# 1. NGẮT

Ngắt là 1 sự kiện khẩn cấp xảy ra trong hay ngoài vi điều khiển. Nó yêu MCU phải dừng chương trình chính và thực thi chương trình ngắt.

**Các loại ngắt thông dụng**

Mỗi ngắt có 1 trình phục vụ ngắt, sẽ yêu cầu MCU thực thi lệnh tại trình phục vụ ngắt khi có ngắt xảy ra. Các ngắt có các địa chỉ cố định trong bộ nhớ để giữ các trình phục vụ. Các địa chỉ này gọi là vector ngắt.







</p>


</details>
