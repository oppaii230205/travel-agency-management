# Project Proposal

## Thành viên nhóm

1.  _Võ Cao Tâm Chính_  
    MSSV: **23120194**
2.  _Nguyễn Hưng Thịnh_  
    MSSV: **23120200**

## Thông tin chi tiết đồ án

### Yêu cầu

1. Yêu cầu cụ thể: Sử dụng mã nguồn được cung cấp sẵn viết lại theo hướng đối tượng (OOP), đông thời bổ sung thêm các cải tiến áp dụng các nguyên tắc (SOLID), các design pattern, nguyên lí dependency injction và áp dụng kiến trúc phần mềm tùy chọn.
2. Thời gian thực hiện: 8 tuần
3. Thực hiện đảm bảo mã nguồn bằng:

   a. Quản lí mã nguồn với git: sinh viên tự lựa chọn qui trình, khuyến khích sử dụng “feature branch workflow”

   b. Tài liệu mô tả coding convention: các tiêu chuẩn thống nhất về mã nguồn mà các thành viên phải tuân theo

   c. Kiểm thử bằng unit test. Cần tạo ra test plan, các test case và test report

4. Tạo ra các tài liệu mô tả kiến trúc phần mềm, mô tả các module:

   a. Vẽ class diagram  
   b. Tạo tài liệu mô tả về các lớp, ý nghĩa các hàm

### Cách thức đánh giá

1. Teamwork: 15%. Phân công và theo dõi tiến độ công việc, biên bản họp nhóm.
2. UI/UX: 20%. Chính là điểm chức năng cũng như giao diện của chương trình.
3. Kiến trúc phần mềm + design pattern: 20%. Mô tả bạn đã thiết kế chương trinh theo kiến trúc phần mềm ra sao, tuân thủ theo các nguyên tắc và nguyên lí OOP như thế nào, dùng các design pattern gì.
4. Đảm bảo chất lượng: 20%. test / coding convention.
5. Tài liệu mô tả kiến trúc phần mềm và các module: 10%
6. Các chủ đề nâng cao: 15%. Là các chủ đề có độ khó, độ phức tạp ở mức cao nhóm tự tìm hiểu mà giáo viên không đề cập trên lớp.

<!-- ## Cách thức quản lý nhóm -->

## Đề tài được chọn: [**Travel Agency Management System**](https://www.codewithc.com/travel-agency-management-system-in-c-with-mysql/)

### Tình trạng hiện tại

- Tổ chức mã nguồn còn rời rạc, thiếu tính liên kết.
- Giao diện console app, chưa thực sự thân thiện & gần gũi với người dùng.
- Thiết kế cơ sở dữ liệu còn đơn giản, chưa thực sự chứa đựng đầy đủ thông tin cần thiết.
- Logic chương trình còn sơ khai, chưa hình thành được các luồng sự kiện chính sẽ xuất hiện.

### Kiến trúc phần mềm áp dụng

- Kiến trúc phần mềm được sử dụng trong đồ án: **Mô hình 3-layer**
- Giới thiệu mô hình: gồm có 3 phần chính (hay còn gọi là **lớp**)

  - **Presentation Layer (GUI):** Lớp này có nhiệm vụ chính giao tiếp với người dùng. Nó gồm các thành phần giao diện và thực hiện các công việc như nhập liệu, hiển thị dữ liêu, kiểm tra tính đúng đắn dữ liệu trước khi gọi lớp Business Logic Layer (BLL).

  - **Business Logic Layer (BLL):** Layer này phân ra 2 thành nhiệm vụ:

    - Đây là nơi đáp ứng các yêu cầu thao tác dữ liệu của GUI layer, xử lý chính nguồn dữ liệu từ Presentation Layer trước khi truyền xuống Data Access Layer và lưu xuống hệ quản trị CSDL.
    - Đây còn là nơi kiểm tra các ràng buộc, tính toàn vẹn và hợp lệ dữ liệu, thực hiện tính toán và xử lý các yêu cầu nghiệp vụ, trước khi trả kết quả về Presentation Layer.

  - **Data Access Layer (DAL):** Lớp này có chức năng giao tiếp với hệ quản trị CSDL như thực hiện các công việc liên quan đến lưu trữ và truy vấn dữ liệu ( tìm kiếm, thêm, xóa, sửa,…).

#### Chi tiết mô tả kiến trúc phần mềm

- Presentation Layer (GUI)

  Trách nhiệm:

  - Giao tiếp trực tiếp với người dùng thông qua giao diện đồ họa (Qt Widgets).

  - Hiển thị dữ liệu từ Business Logic Layer (BLL) và chuyển tương tác người dùng (nhấn nút, nhập liệu) xuống BLL.

  Thành phần chính:

  - LoginWindow: Xử lý đăng nhập/đăng ký, kết nối với AuthService.

  - MainWindow: Cửa sổ chính hiển thị chức năng theo vai trò người dùng (admin/customer).

  - Các Dialog (AddTripDialog, TripListDialog,...): Tạo giao diện cụ thể cho từng nghiệp vụ.

- Business Logic Layer (BLL)

  Trách nhiệm:

  - Xử lý nghiệp vụ: kiểm tra quyền, validate dữ liệu, tính toán.

  - Đóng vai trò trung gian giữa GUI và Data Access Layer (DAL).

  Thành phần chính:

  - AuthService:

    - Quản lý đăng nhập, phân quyền (admin/customer)..

  - TripService, UserService,...:

    - Kiểm tra quyền trước khi thực hiện các chức năng.

    - Chuyển dữ liệu hợp lệ xuống DAL.

- Data Access Layer (DAL)

  Trách nhiệm:

  - Giao tiếp với database: thực thi truy vấn SQL, ánh xạ dữ liệu thành đối tượng.

  - Đảm bảo tính toàn vẹn dữ liệu.

  Thành phần chính:

  - Repository Pattern:

    - SqlUserRepository: Quản lý truy vấn liên quan đến bảng User.

    - SqlTripRepository: Xử lý các thao tác với bảng Trip.

  - DatabaseManager:

    - Quản lý kết nối database dùng Singleton Pattern.

    - Hỗ trợ transaction và bắt lỗi SQL.

- Ví dụ tương tác giữa các lớp:

  - GUI gọi phương thức từ BLL (ví dụ: tripService->addTrip(trip)).
  - BLL kiểm tra nghiệp vụ, gọi DAL để lưu dữ liệu.
  - DAL thực thi SQL và trả kết quả ngược lên BLL → GUI.

  ```mermaid
   flowchart TD
      A[Presentation Layer] -->|Request| B[Business Logic Layer]
      B -->|Validate| C[Data Access Layer]
      C -->|SQL Query| D[(Database)]
      D -->|Result| C --> B --> A
  ```

### Các tính năng chính đã có

1. Tạo mới chuyến đi cho người dùng

2. Hiển thị danh sách người dùng hiện tại

3. Tìm kiếm người dùng cụ thể

4. Cập nhật lại thông tin người dùng

5. Xóa người dùng

6. Tạo chuyến đi mới

7. Cập nhật lại thông tin chuyến đi

8. Xóa chuyến đi

### Mở rộng

1. Tạo giao diện cho phần mềm

   - Thay vì sử dụng đồ họa console như mã nguồn đã có sẵn, chương trình sẽ được xây dựng thêm **GUI (Graphic User Interface)**, giúp các thao tác trên phần mềm trở nên dễ dàng và trực quan hơn.
   - Framework được sử dụng sẽ là: **Qt** _(có thể thay đổi nếu tìm thấy framework phù hợp hơn)_

2. Chức năng đăng nhập / tạo tài khoản mới

   - Thêm chức năng đăng nhập & tạo tài khoản. Người dùng cần phải có tài khoản để sử dụng phần mềm này.
   - Thông tin tài khoản (tên đăng nhập, mật khẩu, họ tên,...) sẽ đều được lưu trên CSDL, giúp xác thực được người dùng cho nhiều phiên đăng nhập.
   - Bên cạnh đó, thông tin tài khoản còn lưu thêm **vai trò (role)** cụ thể của người dùng, giúp phân quyền các nhóm chức năng cho từng loại user khác nhau.

3. Phân quyền người dùng

   - Đối với mỗi loại người dùng cụ thể (VD: quản trị viên, người dùng thường,...) sẽ có các quyền khác nhau, thay vì có thể thực hiện được mọi chức năng như trong mã nguồn có sẵn. VD: người dùng thường chỉ có thể tạo lập, cập nhật thông tin của họ, chứ không thể thay đổi thông tin của người dùng khác.

4. Thêm module **Review** để lưu trữ đánh giá của người dùng cho chuyến đi tương ứng

   - Mỗi user sẽ có thể đưa ra đánh giá cho các chuyến đi mình đã trải nghiệm.
   - Thông tin 1 bản ghi đánh giá bao gồm: đoạn văn đánh giá (text), điểm rating (1-5), thời gian tạo, chuyến đi được đánh giá, người đánh giá.
   - Chức năng hiển thị các bài đánh giá cho từng chuyến đi cụ thể, hiển thị các bài đánh giá của người dùng hiện đang đăng nhập.

5. Xuất hóa đơn khi khách hàng xác nhận
   - Mỗi khi khách hàng xác nhận chuyến đi hệ thống sẽ tự động tính toán chi phí và xuất ra hóa đơn ra file .txt.
   - Hóa đơn bao gồm: Tên khách hàng, số điện thoại, ngày lập, thông tin chuyến đi, tổng thành tiền.
6. Hiển thị thời tiết tại điểm đến
   - Hiển thị thời tiết 5 ngày tiếp theo tại điểm đến trong chuyến đi đang được khách hàng lựa chọn.
   - Thông tin hiển thị bao gồm: Tên điểm đến, ngày dự đoán, nhiệt độ dự đoán, trạng thái thời tiết.
7. Chuyển đổi ngôn ngữ hiển thị
   - Trên giao diện phần mềm cung cấp tính năng chuyển đổi giữa hai ngôn ngữ Việt - Anh.

### Các nguyên tắc và nguyên lí OOP đã tuân thủ

_(sẽ hoàn thiện sau)_

### Các Design Pattern đã áp dụng

_(sẽ hoàn thiện sau)_

## Timeline & Tasks

### Giai đoạn: 3/4 – 9/4

| **Công việc dự kiến**                                                                                                                                                                                                        | **Ước lượng (man hour)** | **Sản phẩm** |
| ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------ | ------------ |
| - Nhận yêu cầu từ giảng viên <br> - Lựa chọn mã nguồn phù hợp <br> - Lên kế hoạch, chọn công cụ bắt đầu dự án <br> - Đề xuất các phương án mở rộng mã nguồn <br> - Tìm hiểu nguyên tắc, design pattern, dependency injection | 28                       | Project Plan |

---

### Sprint 1: 10/4 – 20/5

| Công việc                                   | Ước lượng (man-hour) | Sản phẩm                         |
| ------------------------------------------- | -------------------- | -------------------------------- |
| Thống nhất tài liệu mô tả coding convention | 16                   | Tài liệu mô tả coding convention |
| Thiết kế lại mã nguồn hướng đối tượng       | 28                   | Class Diagram                    |
| Thiết kế cơ sở dữ liệu                      | 12                   | Database Schema                  |
| Thiết kế giao diện (UI)                     | 12                   | Bản phát họa giao diện           |
| Xây dựng CSDL trên SQL Server               | 20                   | Cơ sở dữ liệu trên SQL Server    |
| Viết mã nguồn cho toàn bộ dự án             | 56                   | Mã nguồn hoàn chỉnh              |
| Vẽ giao diện cho sản phẩm                   | 32                   | Giao diện sản phẩm               |

---

### Sprint 2: 21/5 – 27/5

| Công việc                       | Ước lượng (man-hour) | Sản phẩm            |
| ------------------------------- | -------------------- | ------------------- |
| Kiểm thử bằng unit test         | 4                    | Báo cáo kiểm thử    |
| Kiểm thử truy vấn cơ sở dữ liệu | 4                    | Báo cáo kiểm thử    |
| Kiểm thử giao diện              | 4                    | Báo cáo kiểm thử    |
| Sửa lỗi và hoàn thiện sản phẩm  | 16                   | Sản phẩm hoàn thiện |

---

### Finalizing: 28/5 – 30/5

| Công việc                                        | Ước lượng (man-hour) | Sản phẩm                            |
| ------------------------------------------------ | -------------------- | ----------------------------------- |
| Hoàn thành Auto-generated Documentation          | 4                    | Tài liệu Oxygen comment             |
| Hoàn thành nhật kí, báo cáo, tài liệu giới thiệu | 8                    | Tài liệu hoàn chỉnh phục vụ báo cáo |

---
