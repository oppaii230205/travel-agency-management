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

## Cách thức quản lý nhóm



## Timeline & Tasks

### Giai đoạn: 3/4 – 9/4

| **Công việc dự kiến**                                                                                                                                                             | **Ước lượng (man hour)** | **Sản phẩm**     |
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------|------------------|
| - Nhận yêu cầu từ giảng viên  <br> - Lựa chọn mã nguồn phù hợp  <br> - Lên kế hoạch, chọn công cụ bắt đầu dự án <br> - Đề xuất các phương án mở rộng mã nguồn <br> - Tìm hiểu nguyên tắc, design pattern, dependency injection | 28                        | Project Plan     |

---

### Sprint 1: 10/4 – 20/5

| Công việc                                         | Ước lượng (man-hour) | Sản phẩm                              |
|--------------------------------------------------|-----------------------|---------------------------------------|
| Thống nhất tài liệu mô tả coding convention      | 16                    | Tài liệu mô tả coding convention      |
| Thiết kế lại mã nguồn hướng đối tượng            | 28                    | Class Diagram                         |
| Thiết kế cơ sở dữ liệu                           | 12                    | Database Schema                       |
| Thiết kế giao diện (UI)                          | 12                    | Bản phát họa giao diện                |
| Xây dựng CSDL trên SQL Server                    | 20                    | Cơ sở dữ liệu trên SQL Server         |
| Viết mã nguồn cho toàn bộ dự án                 | 56                    | Mã nguồn hoàn chỉnh                   |
| Vẽ giao diện cho sản phẩm                        | 32                    | Giao diện sản phẩm                    |

---

### Sprint 2: 21/5 – 27/5

| Công việc                                | Ước lượng (man-hour) | Sản phẩm             |
|-----------------------------------------|-----------------------|----------------------|
| Kiểm thử bằng unit test                 | 4                     | Báo cáo kiểm thử     |
| Kiểm thử truy vấn cơ sở dữ liệu         | 4                     | Báo cáo kiểm thử     |
| Kiểm thử giao diện                      | 4                     | Báo cáo kiểm thử     |
| Sửa lỗi và hoàn thiện sản phẩm          | 16                    | Sản phẩm hoàn thiện  |

---

### Finalizing: 28/5 – 30/5

| Công việc                                             | Ước lượng (man-hour) | Sản phẩm                                      |
|------------------------------------------------------|-----------------------|-----------------------------------------------|
| Hoàn thành Auto-generated Documentation             | 4                     | Tài liệu Oxygen comment                       |
| Hoàn thành nhật kí, báo cáo, tài liệu giới thiệu     | 8                     | Tài liệu hoàn chỉnh phục vụ báo cáo           |

---




## Đề tài được chọn

### ...

### Tính năng chính

1. Tạo mới chuyến đi cho người dùng

   - Đầu tiên, người dùng có thể nhập thông tin của khách du lịch như tên người dùng, địa chỉ, số điện thoại, email, ngày khởi hành, mã chuyến đi và chi phí chuyến đi.
   - Sau đó, câu lệnh **insert** sẽ thực hiện chèn dữ liệu vào cơ sở dữ liệu.
   - Nếu toàn bộ quá trình thực thi thành công, chương trình sẽ hiển thị kết quả thông báo thành công.

2. Hiển thị danh sách người dùng hiện tại

   - Ở đầu chương trình, câu lệnh **select** sẽ được thực thi để nhận thông tin người dùng từ CSDL.
   - Sau đó, toàn bộ dữ liệu sẽ được hiển thị trên bảng điều khiển.

3. Tìm kiếm người dùng cụ thể

   - Người dùng có thể tìm kiếm bất kỳ bản ghi nào từ cơ sở dữ liệu.
   - Việc tìm kiếm được thực hiện thông qua tên người dùng.
   - Người dùng có thể tìm kiếm chỉ với một ký tự nếu ký tự đó khớp với một hàng trong cột tương ứng.
   - Sau đó, tùy theo lựa chọn của người dùng, chương trình sẽ hiển thị kết quả mong muốn.
   - Cuối cùng, mã lệnh Exit Code sẽ được thực thi để quay lại menu, lặp lại hàm hoặc thoát khỏi bảng điều khiển.

4. Cập nhật lại thông tin người dùng

   - Chương trình cho phép chỉnh sửa thông tin của người dùng.
   - Đầu tiên, câu lệnh **select** sẽ được thực thi để lấy danh sách người dùng hiện có.
   - Sau đó, người dùng nhập vào ID của cột cần chỉnh sửa. Dữ liệu nhập vào sẽ được kiểm tra hợp lệ bằng bộ kiểm tra số (number validator).
   - Tiếp theo, chương trình sẽ kiểm tra xem bản ghi có tồn tại trong cơ sở dữ liệu hay không. Nếu không tìm thấy, chương trình sẽ hiển thị thông báo lỗi dưới dạng hộp thoại (pop-up message) “Không tìm thấy mục”.
   - Nếu tìm thấy bản ghi, chương trình sẽ hiển thị thông tin tương ứng trên bảng điều khiển.
   - Người dùng có thể chỉnh sửa thông tin theo nhu cầu.
   - Ký hiệu ‘X’ được sử dụng để giữ nguyên dữ liệu cũ trong cơ sở dữ liệu.
   - Cuối cùng, câu lệnh Update sẽ được thực thi để cập nhật bản ghi mới theo thông tin người dùng đã cung cấp, và hiển thị thông báo cập nhật thành công.
   - Sau cùng, mã lệnh Exit Code sẽ chạy để quay lại menu, lặp lại chức năng hoặc thoát khỏi bảng điều khiển.

5. Xóa người dùng

   - Hàm này cho phép xóa bản ghi người dùng.
   - Câu lệnh Delete được sử dụng để xóa bản ghi khỏi cơ sở dữ liệu.
   - Trước tiên, chương trình sẽ hiển thị toàn bộ các bản ghi hiện có, sau đó yêu cầu người dùng nhập ID của cột cần xóa.
   - Dữ liệu đầu vào sẽ được kiểm tra bằng bộ kiểm tra số (number validator), vì vậy người dùng chỉ có thể nhập số, không được sử dụng các ký tự khác.
   - Tiếp theo, chương trình kiểm tra xem bản ghi đó có tồn tại trong cơ sở dữ liệu hay không.
   - Nếu bản ghi tồn tại, chương trình sẽ tiến hành xóa bản ghi; nếu không, chương trình sẽ hiển thị thông báo “Không tồn tại trong cơ sở dữ liệu” trên bảng điều khiển.
   - Cuối cùng, mã lệnh Exit Code sẽ được thực thi để quay lại menu, lặp lại chức năng hoặc thoát khỏi bảng điều khiển.

6. Tạo chuyến đi mới

   - Trong hàm này, người dùng có thể thêm bản ghi chuyến đi mới.
   - Người dùng nhập tên chuyến đi và thông tin đó sẽ được thêm vào cơ sở dữ liệu.
   - Sau khi người dùng nhập liệu, chương trình sẽ thực thi câu lệnh **insert_query** (một biến chứa câu lệnh chèn dữ liệu).
   - Sau đó, chương trình sẽ hiển thị thông báo thêm thành công.
   - Cuối cùng, mã lệnh Exit Code sẽ được thực thi để quay lại menu, lặp lại chức năng hoặc thoát khỏi bảng điều khiển.

7. Cập nhật lại thông tin chuyến đi

   - Chương trình cho phép chỉnh sửa thông tin của bản ghi chuyến đi.
   - Đầu tiên, câu lệnh **select** sẽ được thực thi để lấy danh sách các bản ghi chuyến đi hiện có.
   - Sau đó, người dùng sẽ nhập ID của cột cần chỉnh sửa. Dữ liệu đầu vào sẽ được kiểm tra hợp lệ bằng bộ kiểm tra số (number validator).
   - Tiếp theo, chương trình sẽ kiểm tra xem bản ghi có tồn tại trong cơ sở dữ liệu hay không. Nếu không tìm thấy, chương trình sẽ hiển thị hộp thoại thông báo (pop-up message) “Không tìm thấy mục”.
   - Nếu bản ghi tồn tại, chương trình sẽ hiển thị thông tin bản ghi đó trên bảng điều khiển để người dùng xem và chỉnh sửa.

8. Xóa chuyến đi

   - Hàm này cho phép xóa bản ghi chuyến đi.
   - Câu lệnh **delete** được sử dụng để xóa bản ghi khỏi cơ sở dữ liệu.
   - Trước tiên, chương trình sẽ hiển thị tất cả các bản ghi hiện có, sau đó yêu cầu người dùng nhập ID của cột cần xóa.
   - Dữ liệu đầu vào sẽ được kiểm tra bằng bộ kiểm tra số (number validator), do đó người dùng chỉ có thể nhập các ký tự số, không được dùng ký tự khác.
   - Tiếp theo, chương trình kiểm tra xem bản ghi đó có tồn tại trong cơ sở dữ liệu hay không.
   - Nếu có, chương trình sẽ tiến hành xóa bản ghi; nếu không, chương trình sẽ hiển thị thông báo “Không tồn tại trong cơ sở dữ liệu” trên bảng điều khiển.
   - Cuối cùng, mã lệnh Exit Code sẽ được thực thi để quay lại menu, lặp lại chức năng hoặc thoát khỏi bảng điều khiển.

### Mở rộng

1. Tạo giao diện cho phần mềm

   - Thay vì sử dụng đồ họa console như mã nguồn đã có sẵn, chương trình sẽ được xây dựng thêm **GUI (Graphic User Interface)**, giúp các thao tác trên phần mềm trở nên dễ dàng và trực quan hơn.
   - Framework được sử dụng sẽ là: **Qt**

2. Chức năng đăng nhập / tạo tài khoản mới

   - Thêm chức năng đăng nhập & tạo tài khoản. Người dùng cần phải có tài khoản để sử dụng phần mềm này.

3. Phân quyền người dùng

   - Đối với mỗi loại người dùng cụ thể (VD: quản trị viên, người dùng thường,...) sẽ có các quyền khác nhau, thay vì có thể thực hiện được mọi chức năng như trong mã nguồn có sẵn. VD: người dùng thường chỉ có thể tạo lập, cập nhật thông tin của họ, chứ không thể thay đổi thông tin của người dùng khác.

### Kiến trúc phần mềm

- Kiến trúc phần mềm được sử dụng trong đồ án: **Mô hình 3-layer**
- Giới thiệu mô hình: gồm có 3 phần chính (hay còn gọi là lớp)

  - **Presentation Layer (GUI):** Lớp này có nhiệm vụ chính giao tiếp với người dùng. Nó gồm các thành phần giao diện và thực hiện các công việc như nhập liệu, hiển thị dữ liêu, kiểm tra tính đúng đắn dữ liệu trước khi gọi lớp Business Logic Layer (BLL).
  - **Business Logic Layer (BLL):** Layer này phân ra 2 thành nhiệm vụ:

    - Đây là nơi đáp ứng các yêu cầu thao tác dữ liệu của GUI layer, xử lý chính nguồn dữ liệu từ Presentation Layer trước khi truyền xuống Data Access Layer và lưu xuống hệ quản trị CSDL.
    - Đây còn là nơi kiểm tra các ràng buộc, tính toàn vẹn và hợp lệ dữ liệu, thực hiện tính toán và xử lý các yêu cầu nghiệp vụ, trước khi trả kết quả về Presentation Layer.

  - **Data Access Layer (DAL):** Lớp này có chức năng giao tiếp với hệ quản trị CSDL như thực hiện các công việc liên quan đến lưu trữ và truy vấn dữ liệu ( tìm kiếm, thêm, xóa, sửa,…).

- Ưu điểm:

  - Việc phân chia thành từng lớp giúp cho code được tường minh hơn. Nhờ vào việc chia ra từng lớp đảm nhận các chức năng khác nhau và riêng biệt như giao diện, xử lý, truy vấn thay vì để tất cả lại một chỗ. Nhằm giảm sự kết dính (_decoupling_).
  - Dễ bảo trì: Khi được phân chia, thì một thành phần của hệ thống sẽ dễ thay đổi. Việc thay đổi này có thể được cô lập trong 1 lớp, hoặc ảnh hưởng đến lớp gần nhất mà không ảnh hưởng đến cả chương trình.
  - Dễ phát triển, tái sử dụng: Khi chúng ta muốn thêm một chức năng nào đó thì việc lập trình theo một mô hình sẽ dễ dàng hơn vì chúng ta đã có chuẩn để tuân theo.
  - Dễ bàn giao: Nếu mọi người đều theo một quy chuẩn đã được định sẵn, thì công việc bàn giao, tương tác với nhau sẽ dễ dàng hơn và tiết kiệm được nhiều thời gian.
  - Dễ phân phối khối lượng công việc. Mỗi một nhóm, một bộ phận sẽ nhận một nhiệm vụ trong mô hình 3 lớp. Việc phân chia rõ ràng như thế sẽ giúp các lập trình viên kiểm soát được khối lượng công việc của mình.

### Các nguyên tắc và nguyên lí OOP đã tuân thủ

### Các Design Pattern đã áp dụng
