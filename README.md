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

![Screenshot 2024-03-17 191704](https://github.com/DangTruongBT/Embedded-C/assets/103482832/895d90f8-2b22-408d-b16e-7984e75c81e8)

**Quá trình ngắt:**

![Screenshot 2024-03-17 191833](https://github.com/DangTruongBT/Embedded-C/assets/103482832/8806bef4-c078-4d10-97e9-c8d5ea3873a1)

  *Ngắt ngoài*

  Xảy ra khi có thay đổi điện áp trên các chân GPIO được cấu hình làm ngõ vào ngắt.

     - LOW: kích hoạt ngắt liên tục khi chân ở mức thấp.
     
     - HIGH: Kích hoạt liên tục khi chân ở mức cao.
     
     - Rising: Kích hoạt khi trạng thái trên chân chuyển từ thấp lên cao.
     
     - Falling: Kích hoạt khi trạng thái trên chân chuyển từ cao xuống thấp.

![Screenshot 2024-03-17 192243](https://github.com/DangTruongBT/Embedded-C/assets/103482832/2addd5a2-c80e-412f-ad9d-c4f956af4961)

 *Ngắt TIMER*
 
Ngắt Timer xảy ra khi giá trị trong thanh ghi đếm của timer tràn. Giá trị tràn được xác định bởi giá trị cụ thể trong thanh ghi đếm của timer.
Vì đây là ngắt nội trong MCU, nên phải reset giá trị thanh ghi timer để có thể tạo được ngắt tiếp theo.

 *Ngắt truyền thông*

 Ngắt truyền thông xảy ra khi có sự kiện truyền/nhận dữ liệu giữ MCU với các thiết bị bên ngoài hay với MCU. Ngắt này sử dụng cho nhiều phương thức như Uart, SPI, I2C…v.v nhằm đảm bảo việc truyền nhận chính xác.

 ![Screenshot 2024-03-17 192520](https://github.com/DangTruongBT/Embedded-C/assets/103482832/2ca78b4c-6b69-4cd3-9fa7-da68e60cfdd2)

 **Độ ưu tiên ngắt**
 
 Độ ưu tiên ngắt là khác nhau ở các ngắt. Nó xác định ngắt nào được quyền thực thi khi nhiều ngắt xảy ra đồng thời.

 STM32 quy định ngắt nào có số thứ tự ưu tiên càng thấp thì có quyền càng cao. Các ưu tiên ngắt có thể lập trình được.

 # 2.TIMER
 
Có thể hiểu 1 cách đơn giản: timer là 1 mạch digital logic có vai trò đếm mỗi chu kỳ clock (đếm lên hoặc đếm xuống).

Timer còn có thể hoạt động ở chế độ counter, nó sẽ nhận xung clock từ các tín hiệu ngoài. Có thể là từ 1 nút nhấn, bộ đếm sẽ được tăng sau mỗi lần bấm nút (sườn lên hoặc sườn xuống tùy vào cấu hình).

Ngoài ra còn các chế độ khác:

· PWM Mode · Advanced PWM Mode · Output Compare Mode · One-Pulse Mode · Input Capture Mode · Encoder Mode · Timer Gate Mode · Timer DMA Burst Mode · IRTIM Infrared Mode

STM32f103C8 có tất cả 7 timer nhưng trong đó đã bao gồm 1 systick timer, 2 watchdog timer. Vậy chỉ còn lại 4 timer dùng cho các chức năng như ngắt, timer base, PWM, Encoder, Input capture…. Trong đó TIM1 là Timer đặc biệt, chuyên dụng cho việc xuất xung với các mode xuất xung, các mode bảo vệ đầy đủ hơn so với các timer khác. TIM1 thuộc khối clock APB2, còn các TIM2,TIM3,TIM4 thuộc nhóm APB1.

  **Timer clock**
  
  Khi không có cấu hình gì liên quan đến clock và đã gắn đúng thạch anh ngoài trên chân PD0(5) và PD1(6) thì clock tương ứng của TIM1,TIM2,TIM3,TIM4 đã là 72Mhz. Cần ghi nhớ là sử dụng timer nào thì cấp clock cho timer đó theo đúng nhánh clock.

  **Prescaler**

  Prescaler là bộ chia tần số của timer. Bộ chia này có giá trị tối đa là 16 bit tương ứng với giá trị là 65535. Các giá trị này có thể được thay đổi và điều chỉnh bằng lập trình. Tần số sau bộ chia này sẽ được tính là:

        FCK_CNT = fCK_PSC/(PSC+1).

 FCK_CNT: tần số sau bộ chia.

 fCK_PSC: tần số clock đầu vào cấp cho timer.

 PSC: chính là giá trị truyền vào được lập trình bằng phần mềm

 **Cấu hình Timer**

        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2, ENABLE);


</p>

</details>


<details><summary>LESSON 3: CÁC CHUẨN GIAO TIẾP</summary>
<p>
	
Các MCU truyền nhận dữ liệu với nhau hoặc với các thiết bị thông qua tín hiệu điện áp. MCU có thể truyền nhận song song, nối tiếp các tín hiệu điện áp này thông quá các chân được cấu hình riêng biệt.

Để việc truyền nhận được dễ dàng với nhiều dòng MCU và phần cứng, các chuẩn giao tiếp được tạo ra. Vi điều khiển sẽ sử dụng các chuẩn giao tiếp khác nhau để liên lạc với nhau hoặc liên lạc với các thiết bị khác hay các phần tử khác trên mạch. Có thể kể đến như I2C, SPI, UART, ….

# 1.SPI  - Serial Peripheral Interface

SPI – Serial Peripheral Interface – hay còn gọi là giao diện ngoại vi nối tiếp, được phát triển bởi hãng Motorola. Chuẩn đồng bộ nối truyền dữ liệu ở chế độ full - duplex (hay gọi là "song công toàn phần". Nghĩa là tại 1 thời điểm có thể xảy ra đồng thời quá trình truyền và nhận. Là giao tiếp đồng bộ, bất cứ quá trình nào cũng đều được đồng bộ với xung clock sinh ra bởi thiết bị Master
Tốc độ truyền thông cao: SPI cho phép truyền dữ liệu với tốc độ rất nhanh, thường đạt được tốc độ Mbps hoặc thậm chí hàng chục Mbps. Điều này rất hữu ích khi cần truyền dữ liệu nhanh và đáng tin cậy trong các ứng dụng như truyền thông không dây, điều khiển từ xa và truyền dữ liệu đa phương tiện.

![Screenshot 2024-03-17 193833](https://github.com/DangTruongBT/Embedded-C/assets/103482832/ee40b85b-f9a1-425f-b64d-cefafff45156)

**SPI sử dụng 4 đường giao tiếp nên đôi khi được gọi là chuẩn truyền thông “ 4 dây”**

  - SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave. Xung này có chức năng giữ nhịp cho giao tiếp SPI. Mỗi nhịp trên chân SCK báo 1 bit dữ liệu đến hoặc đi → Quá trình ít bị lỗi và tốc độ truyền cao.

  - MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master. Đường MISO phải được kết nối giữa thiết bị Master và Slave.

  - MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. Đường MOSI phải được kết nối giữa thiết bị Master và Slave.

  - SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). Chân này đôi khi còn được gọi là CS (Chip Select). Chân SS của vi điều khiển (Master) có thể được người dùng tạo bằng cách cấu hình 1 chân GPIO bất kỳ chế độ Output.

SPI cho phép 1 MCU chủ giao tiếp với nhiều thiết bị tớ thông qua tín hiệu chọn thiết bị SS. Các thiết bị tớ chỉ có thể có 1 chân CS để nhận tín hiệu chọn này, tuy nhiên thiết bị chủ có thể có nhiều hơn 1 chân SS để chọn từng thiết bị muốn giao tiếp.

*Quá trình truyền nhận SPI:*

![Screenshot 2024-03-17 194800](https://github.com/DangTruongBT/Embedded-C/assets/103482832/2e114d6c-f3f5-42d7-bd6e-5dc562af87b2)


    Bắt đầu quá trình, master sẽ kéo chân CS của slave muốn giao tiếp xuống 0 để báo hiệu muốn truyền nhận.
 
    Clock sẽ được cấp bởi master, tùy vào chế độ được cài, với mỗi xungc clock,  1 bit sẽ được truyền từ master đến slave và slave cũng truyền 1 bit cho master.
 
    Các thanh ghi cập nhật giá trị và dịch 1 bit.
 
    Lặp lại quá trình trên đến khi truyền xong 8 bit trong thanh ghi.
 
    Giao tiếp song công.
    
Chế độ hoạt động: SPI có 4 chế độ hoạt động phụ thuộc vào cực của xung giữ (Clock Polarity – CPOL) và pha (Phase - CPHA). CPOL dùng để chỉ trạng thái của chân SCK ở trạng thái nghỉ. Chân SCK giữ ở mức cao khi CPOL=1 hoặc mức thấp khi CPOL=0. CPHA dùng để chỉ các mà dữ liệu được lấy mẫu theo xung. Dữ liệu sẽ được lấy ở cạnh lên của SCK khi CPHA=0 hoặc cạnh xuống khi CPHA=1.

![Screenshot 2024-03-17 195031](https://github.com/DangTruongBT/Embedded-C/assets/103482832/401de353-c51d-460c-ba9e-57ba1865cdd8)

    Mode 0 (mặc định) – xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh lên) (CPHA = 0).
    
    Mode 1 - xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh xuống) (CPHA = 1).
    
    Mode 2 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh lên) (CPHA = 0).
    
    Mode 3 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh xuông) (CPHA = 1).

# 2.I2C

I2C là chuẩn giao tiếp nối tiếp, chỉ sử dụng 2 dây SDA, SCL.

Một Master giao tiếp được với nhiều Slave.

Truyền bán song công

![Screenshot 2024-03-17 195434](https://github.com/DangTruongBT/Embedded-C/assets/103482832/af50b1b9-95d3-4cdd-a611-f1ceaae06972)


    I2C là giao tiếp đồng bộ

    SDA: Truyền tín hiệu

    SCL: Cung cấp clock phục vụ truyền nhận
    
Trong I2C 2 thiết bị giao tiếp với nhau bởi 1 qui định riêng chúng dựa vào địa chỉ riêng của mỗi SLAVE để giao tiếp. Một lưu ý khi thiết kế phần cứng là treo trở lên mức cao của SDA và SCL, để bảo vệ tín hiệu ổn định và đúng.

**Cách thức hoạt động**

    Ban đầu cả 2 đường truyền SDA và SCL đều ở mức cao. Khi bắt đầu gửi dữ liệu Master thông báo cho SLAVE biết bằng cách kéo SDA xuống mức thấp giữ cho SCL ở mức cao. 

    Master sẽ gửi 7 bit địa chỉ đến SLAVE trong mạng và 1 bit để đọc hay ghi. Nếu có 1 SLAVE trùng khớp với địa chỉ đa gửi đi SLAVE sẽ đáp trả bằng 1 bit ACK thông qua kéo SCL xuống mức thấp
    (Trong trường hợp không có SLAVE nào phản hồi MASTER sẽ không tiếp tục truyền dữ liệu)

    Khi MASTER nhận được ACK từ SLAVE đồng nghĩa với việc 2 bên đã thiết lập kết nối. Từ đó MASTER có thể truyền tín hiệu cho SLAVE mỗi lần truyền là 8 bit khi SLAVE nhẫn đủ sẽ phản hồi bằng cách kéo SCL xuống mức thấp thông báo nó đã nhận đủ

    Quá trình này sẽ lập lại cho đến khi MASTER tạo ra 1 tín hiệu STOP thông báo rằng không có dữ liệu truyền đi nữa. Trái ngược với tín hiệu STAR tín hiệu STOP sẽ kéo SDA lên mức cao trong khi SCL vẫn ở mức cao

    Lưu ý: MASTER hoàn toàn kiểm soát SCL còn SLAVE chỉ thực hiện theo 

    
![Screenshot 2024-03-17 201038](https://github.com/DangTruongBT/Embedded-C/assets/103482832/77d4cc8e-cd78-4949-ba63-bcc2cf65a6ae)

# 3.UART - Universal Asynchronous Receiver-Transmitter

UART (Universal Asynchronous Receiver-Transmitter – Bộ truyền nhận dữ liệu không đồng bộ) là một giao thức truyền thông phần cứng dùng giao tiếp nối tiếp không đồng bộ và có thể cấu hình được tốc độ.

Giao thức UART là một giao thức đơn giản và phổ biến, bao gồm hai đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận). Dữ liệu được truyền và nhận qua các đường truyền này dưới dạng các khung dữ liệu (data frame) có cấu trúc chuẩn, với một bit bắt đầu (start bit), một số bit dữ liệu (data bits), một bit kiểm tra chẵn lẻ (parity bit) và một hoặc nhiều bit dừng (stop bit).

Truyền theo frame gồm 8 bit


![Screenshot 2024-03-17 201438](https://github.com/DangTruongBT/Embedded-C/assets/103482832/c8d139f4-da98-4baa-a9a3-278ffdfc9617)

Để bắt đầu truyền nhận khi có Start Bit (kéo TX từ 1->0).

5 đến 9 bit dữ liệu.

Parity bit (bit chẵn lẻ).

Bit chẵn lẻ kiểm tra xem dữ liệu nhận đúng hay chưa.

Quy luật chẵn: nếu tổng số bit 1 là số chẵn thì bit đó là 0, còn quy luật lẻ là nếu tổng sốt bit lẻ là số chẵn thì thêm số 1.

1 hoặc 2 stop bit().









</p>

</details>
