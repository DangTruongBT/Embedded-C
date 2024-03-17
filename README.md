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

  
</p>


</details>
   
