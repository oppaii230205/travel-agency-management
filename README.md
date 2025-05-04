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

  - `LoginWindow`: Xử lý đăng nhập/đăng ký, kết nối với AuthService.

  - `MainWindow`: Cửa sổ chính hiển thị chức năng theo vai trò người dùng (admin/customer).

  - Các Dialog (`AddTripDialog`, `TripListDialog`,...): Tạo giao diện cụ thể cho từng nghiệp vụ.

- Business Logic Layer (BLL)

  Trách nhiệm:

  - Xử lý nghiệp vụ: kiểm tra quyền, validate dữ liệu, tính toán.

  - Đóng vai trò trung gian giữa GUI và Data Access Layer (DAL).

  Thành phần chính:

  - `AuthService`:

    - Quản lý đăng nhập, phân quyền (admin/customer)..

  - `TripService`, `UserService`,...:

    - Kiểm tra quyền trước khi thực hiện các chức năng.

    - Chuyển dữ liệu hợp lệ xuống DAL.

- Data Access Layer (DAL)

  Trách nhiệm:

  - Giao tiếp với database: thực thi truy vấn SQL, ánh xạ dữ liệu thành đối tượng.

  - Đảm bảo tính toàn vẹn dữ liệu.

  Thành phần chính:

  - Repository Pattern:

    - `SqlUserRepository`: Quản lý truy vấn liên quan đến bảng User.

    - `SqlTripRepository`: Xử lý các thao tác với bảng Trip.

  - `DatabaseManager`:

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

#### Nguyên tắc SOLID

Đồ án tuân thủ nghiêm ngặt 5 nguyên tắc SOLID để đảm bảo tính mở rộng và dễ bảo trì:

**1. Single Responsibility Principle (SRP)**

**Định nghĩa**: Mỗi lớp chỉ có một trách nhiệm duy nhất, dễ dàng quản lí & kiểm soát chương trình.

**Ví dụ áp dụng trong đồ án:**

- Lớp `SqlTripRepository`, `SqlUserRepository`,...

  - Trách nhiệm duy nhất: Thực hiện các thao tác CRUD với bảng `Trip`, `User` trong database.
  - Code minh họa:

  ```cpp
  class SqlTripRepository {
  public:
   bool addTrip(const Trip& trip); // Chỉ thực hiện các thao tác CRUD vào DB
   QList<Trip> getAllTrips(); // Không chứa logic nghiệp vụ
  };

  ```

- Lớp `TripService`, `UserService`, `AuthService`,...

  - Trách nhiệm duy nhất: Chứa các thông tin nghiệp vụ (tính toán, kiểm tra quyền, validation,...), giải quyết bài toán thực tế của phần mềm. Chứa các chức năng, yêu cầu cụ thể phục vụ cho người sử dụng phần mềm.

  - Code minh họa:

  ```cpp
  class TripService {
  public:
   // Basic CRUD operations, lấy dữ liệu thông qua các lớp Repository trước đó, không liên quan đến database thực sự.
   QList<Trip> getAllTrips();

   // Business logic methods
   QList<Trip> findTripsByDifficulty(const QString& difficulty);

   // Validation
   bool validateTrip(const Trip& trip) const;
  }
  ```

- Lớp `AddTripDialog`, `TripListDialog`, `ShowUserInformationDialog`,...

  - Trách nhiệm duy nhất: Định nghĩa giao diện để người dùng có thể tương tác với phần mềm. Không liên quan đến logic nghiệp vụ và database của phần mềm.

  - Code minh họa:

  ```cpp
   namespace Ui {
   class TripListDialog;
   }

   class TripListDialog : public QDialog
   {
      Q_OBJECT

   private:
      void setupModel();
      void refreshTripList();
      void setupActions(); // Thêm hàm thiết lập actions

   private:
      Ui::TripListDialog *ui; // Đặc trưng của Qt khi làm C++ GUI App
      QSharedPointer<TripService> _tripService; // Lấy/Đẩy dữ liệu thông qua lớp Service
      QStandardItemModel* _model; // Model quản lý dữ liệu
   };
  ```

- Lớp `Trip`, `User`, ...

  - Trách nhiệm duy nhất: Đây là các model của phần mềm (hay _Data Transfer Object - DTO_), chỉ dùng để chứa dữ liệu và đi qua các tầng trong kiến trúc phần mềm.

  - Code minh họa:

  ```cpp
   class User {
      private:
         QString _email;
         QString _password;
         QString _name;
         QString _role;
      public:
         User();
         User(const QString& email, const QString& password, const QString& name, const QString& role);

         QString email() const;
         // other getters...

         void setEmail(const QString& email);
         // other setters...

         bool isValid() const;
   };
  ```

- Lợi ích: Trong quá trình phát triển phần mềm, nếu cần thay đổi database schema (thêm ảnh, thông tin, thêm logic nghiệp vụ, chức năng...) thì chỉ cần sửa ở một số lớp cụ thể mà không làm ảnh hưởng tới toàn bộ chương trình.

**2. Open / Closed Principle (OCP)**

**Định nghĩa**: Có thể mở rộng các lớp nhưng không sửa đổi code có sẵn.

**Ví dụ áp dụng trong đồ án:**

- Thêm service mới (ví dụ: `BookingService`, `PaymentService`) bằng cách inject vào GUI thông qua constructor, không cần sửa `MainWindow`.

  - Code minh họa:

  ```cpp
  MainWindow::MainWindow(QSharedPointer<AuthService> authService,
                     QSharedPointer<TripService> tripService,
                     QSharedPointer<BookingService> bookingService)
  ```

- Mở rộng/Thay đổi kiểu database

  - Trách nhiệm duy nhất: Sử dụng interface `TripRepository`, `UserRepository` để sau này có thể thêm kiểu cơ sở dữ liệu phi quan hệ (Ví dụ: `MongoTripRepository`) vào chương trình, không ảnh hưởng đến các lớp khác.

  - Code minh họa:

  ```cpp
   class TripService {
   private:
      QSharedPointer<TripRepository> _repository; // sử dụng interface thay vì concrete class
      bool validateTrip(const Trip& trip) const;

   public:
      explicit TripService(QSharedPointer<TripRepository> repository, QObject* parent = nullptr);
   };
  ```

- Lợi ích: Chương trình sẽ **cho phép** mở rộng thêm các tính năng một cách dễ dàng, linh hoạt để đáp ứng nhu cầu của khách hàng, trong khi **không cho phép** thay đổi code có sẵn - điều sẽ rất dễ gây ra các bug không mong muốn.

**3. Liskov Substitution Principle (LSP)**

**Định nghĩa**: Lớp con phải thay thế được lớp cha mà không phá vỡ chương trình.

**Ví dụ áp dụng trong đồ án:**

- Các repository (`SqlUserRepository`, `SqlTripRepository`) đều kế thừa từ interface (`UserRepository`, `TripRepository`), đảm bảo có thể hoán đổi khi cần chuyển từ SQL sang NoSQL. _(đã trình bày ở nguyên tắc 2 - Open/Closed Principle)_

- Sử dụng cho Testing: Dù là `SqlUserRepository` hay `MockUserRepository` (dùng cho test), `AuthService` vẫn hoạt động đúng.

- Lợi ích: Liskov Substitution Principle (LSP) giúp đảm bảo rằng lớp con có thể thay thế lớp cha mà không làm thay đổi hành vi của hệ thống, từ đó giúp hệ thống ổn định, dễ mở rộng và tránh lỗi do kế thừa sai cách.

**4. Interface Segregation Principle (ISP)**

**Định nghĩa**: Client không nên phụ thuộc vào interface mà nó không dùng.

**Ví dụ áp dụng trong đồ án:**

- Interface **nhỏ, chuyên biệt**: Tách thành 2 interface `TripRepository` và `UserRepository` thay vì một interface lớn `Repository`.

- Vì `AuthService` chỉ cần các thông tin và các hàm liên quan đến `User` như `addUser()`, `getUserByEmail()`,... nên chỉ cần tiêm dependency `UserRepository` vào `AuthService`, giảm sự phụ thuộc thừa.

  - Code minh họa:

  ```cpp
   // ✅ Đúng ISP
   class IUserRepository {
   public:
      virtual bool addUser(const User& user) = 0;
      virtual QSharedPointer<User> getUserByEmail(const QString& email) = 0;
   };

   class ITripRepository {
   public:
      virtual bool addTrip(const Trip& trip) = 0;
      virtual QList<Trip> getAllTrips() = 0;
   };

   //.......
   // Các service
   class AuthService {
   private:
      QSharedPointer<UserRepository> _userRepository; // chỉ phụ thuộc vào UserRepository
      QSharedPointer<User> _currentUser; // lưu lại user hiện tại
   };

  ```

- Lợi ích: Giúp giảm sự phụ thuộc thừa cho chương trình (`AuthService` chỉ phụ thuộc vào `UserRepository`, không biết gì về `TripRepository`), cũng như dễ bảo trì cho chương trình (Thêm/xóa phương thức trong `TripRepository` không làm hỏng `AuthService`).

**5. Dependency Inversion Principle (DIP)**

**Định nghĩa**: Thay vì để module cấp cao không phụ thuộc vào module cấp thấp, cả hai nên phụ thuộc vào abstraction.

**Ví dụ áp dụng trong đồ án:**

- Định nghĩa abstraction (interface) cho repository.

  - Code minh họa:

  ```cpp
   // ✅ Đúng DIP
   class UserRepository {
   public:
      virtual QSharedPointer<User> getUserByEmail(const QString& email) = 0;
      virtual bool addUser(const User& user) = 0;
   };
  ```

- Module cấp cao (AuthService) phụ thuộc vào interface.

  - Code minh họa:

  ```cpp
   class AuthService {
   private:
      QSharedPointer<UserRepository> _userRepo; // Phụ thuộc vào abstraction
   public:
      AuthService(QSharedPointer<UserRepository> repo) : _userRepo(repo) {}
   };
  ```

- Module cấp thấp (`SqlUserRepository`) _implement_ interface.

  - Code minh họa:

  ```cpp
   class SqlUserRepository : public UserRepository {
   public:
      QSharedPointer<User> getUserByEmail(const QString& email) override {
         // Logic truy vấn từ SQL database
      }
   };
  ```

- Sơ đồ mô tả luồng chương trình

  ```mermaid
  sequenceDiagram
   participant GUI as MainWindow
   participant BLL as AuthService
   participant DAL as SqlUserRepository
   GUI->>BLL: login("user@example.com", "pass123")
   BLL->>DAL: getUserByEmail("user@example.com")
   DAL-->>BLL: User object
   BLL-->>GUI: Kết quả đăng nhập
  ```

- Cài đặt code

  - `MainWindow` gọi `AuthService` (cấp cao).
  - `AuthService` gọi `UserRepository` (abstraction), không biết chi tiết là SQL hay NoSQL.

- Ví dụ mở rộng (sử dụng NoSQL Database)

  ```cpp
  class MongoUserRepository : public UserRepository {
  public:
     QSharedPointer<User> getUserByEmail(const QString& email) override {
        // Logic truy vấn từ MongoDB
     }
  };

  // Trong main.cpp
  auto userRepo = QSharedPointer<MongoUserRepository>::create();
  auto authService = QSharedPointer<AuthService>::create(userRepo);
  ```

- Lợi ích: Giảm coupling giữa các lớp. Dễ dàng thay thế, mở rộng module mà không cần sửa code hiện có.

#### Nguyên lí Dependency Injection (DI)

**Định nghĩa**: Cung cấp các dependency (phụ thuộc) từ bên ngoài vào một lớp thay vì để lớp tự khởi tạo chúng.

**Ví dụ áp dụng trong đồ án:**

- Khởi Tạo Dependency: Trong `main.cpp`, tất cả dependency được khởi tạo và inject vào các lớp cần thiết.

  ```cpp
  int main() {
   // 1. Khởi tạo repository
   auto userRepo = QSharedPointer<SqlUserRepository>::create(DatabaseManager::getInstance());

   // 2. Inject repository vào AuthService
   auto authService = QSharedPointer<AuthService>::create(userRepo);

   // 3. Inject AuthService vào LoginWindow
   LoginWindow loginWindow(authService);
  }
  ```

- DI Trong Service Layer: `TripService` nhận `TripRepository` qua constructor.

  ```cpp
  class TripService {
  private:
     QSharedPointer<TripRepository> _tripRepo;
  public:
     TripService(QSharedPointer<TripRepository> repo) : _tripRepo(repo) {}

     bool addTrip(const Trip& trip) {
        return _tripRepo->addTrip(trip); // Gọi abstraction, không phụ thuộc implementation
     }
  };
  ```

- DI Trong UI Layer: `MainWindow` nhận các service qua constructor.

  ```cpp
  MainWindow::MainWindow(QSharedPointer<AuthService> authService,
                       QSharedPointer<TripService> tripService)
     : _authService(authService), _tripService(tripService)
  {
     // Kết nối signal-slot
     connect(_tripService.data(), &TripService::tripAdded,
           this, &MainWindow::onTripAdded);
  }
  ```

**Lợi ích**: DI là xương sống của kiến trúc phần mềm hiện đại, giúp đồ án trở nên linh hoạt, dễ bảo trì. Đây còn là nền tảng để áp dụng nguyên tắc SOLID. Kết hợp cùng Interface để tuân thủ _Dependency Inversion Principle (DIP)_ và _Smart Pointer_ để quản lí vùng nhớ an toàn.

### Các Design Pattern đã áp dụng

_(sẽ hoàn thiện sau)_


### Hướng dẫn Coding Invention

#### Mục đích

- Tăng tính rõ ràng, bảo trì
- Giảm lỗi tiềm ẩn
- Tối ưu hiệu năng
- Tuân thủ best practices từ C++ Core Guidelines

#### Các quy tắc cần tuân thủ

Quản lý Header Files (SF)
- SF.7: Không dùng “using namespace” ở global scope trong header file
- SF.8: Luôn dùng #include guards
- SF.12: Dùng “” cho file local, <> cho system/library

Ví dụ:
```cpp
//SF.8: #include guard
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

//SF.7: Không dùng 'using namespace' ở global scope

//SF.12: Include thư viện hệ thống với <>
#include <cmath>
double squareRoot(double x) {
    return std::sqrt(x);  // Không cần 'using namespace std'
}

#endif // MATH_UTILS_H
```
Style & Readability (NL)
- NL.21 / ES.10: Khai báo một biến mỗi dòng
- NL.18: Dùng C++-style declarator
- NL.5: Tránh mã hóa kiểu vào tên biến

Ví dụ:
```cpp
#include <string>

int main() {
    std::string userName = "John";
    int userId = 12345;
    int* pointer = nullptr;
    //NL.18: C++-style declarator (đặt * và & sát kiểu dữ liệu)
    //NL.5: Không mã hóa kiểu vào tên biến
    //NL.21: Mỗi biến khai báo trên 1 dòng
    
    return 0;
}
```
Khởi tạo & Phạm vi Biến (ES)
- ES.20: Luôn khởi tạo biến
- ES.21: Khai báo biến gần nơi dùng nhất
- ES.22: Chỉ khai báo khi có giá trị khởi tạo
- NR.1: Không bắt buộc khai báo ở đầu hàm

Ví dụ:
```cpp
#include <iostream>
#include <vector>
#include <random>

int main() {
    //ES.20: Luôn khởi tạo biến ngay khi khai báo
    const int maxAttempts = 3;  // Khởi tạo ngay
    std::vector<int> numbers = {1, 2, 3};  // Khởi tạo ngay

    //NR.1: Không bắt buộc khai báo tất cả biến ở đầu hàm
    for (int i = 0; i < maxAttempts; ++i) {
        //ES.21: Khai báo biến gần nơi dùng nhất
        std::random_device rd;
        std::mt19937 gen(rd());

        //ES.22: Chỉ khai báo khi có giá trị khởi tạo
        const int randomValue = std::uniform_int_distribution<>(1, 100)(gen);

        std::cout << "Lần thử " << i + 1 << ": " << randomValue << '\n';

        if (randomValue > 50) {
            //ES.21: Khai báo biến ngay khi cần
            const std::string successMsg = "Thành công!";
            std::cout << successMsg << '\n';
            break;
        }
    }

    return 0;
}
```
Xử lý Lỗi & Logic (F, NR)
- NR.3: Ưu tiên dùng exception thay vì error code
- F.56: Tránh lồng điều kiện không cần thiết
- NR.2: Không bắt buộc một return duy nhất

Ví dụ:
```cpp
#include <iostream>
#include <stdexcept>
#include <string>

// Hàm đăng nhập sử dụng exception (NR.3)
void login(const std::string& username, const std::string& password) {
    if (username.empty()) {
        throw std::invalid_argument("Tên đăng nhập không được trống");
    }
    if (password.empty()) {
        throw std::invalid_argument("Mật khẩu không được trống");
    }
    if (password.length() < 6) {
        throw std::runtime_error("Mật khẩu phải có ít nhất 6 ký tự");
    }
    
    std::cout << "Đăng nhập thành công!\n";
}

int main() {
    try {
        std::string username = "user123";
        std::string password = "pass";  // Mật khẩu ngắn để demo lỗi

        // F.56: Tránh lồng điều kiện không cần thiết bằng cách dùng early return
        if (username == "admin") {
            std::cout << "Chào admin!\n";
            return 0;  // NR.2: Không bắt buộc 1 return duy nhất
        }

        login(username, password);

        // Các xử lý khác...
        std::cout << "Thực hiện các thao tác...\n";
        return 0;  // NR.2: Có thể có nhiều return

    } catch (const std::exception& e) {  // NR.3: Bắt exception
        std::cerr << "Lỗi: " << e.what() << "\n";
        return 1;
    }
}
```
Hằng số & So sánh (ES)
- ES.45: Tránh magic numbers, dùng hằng số
- Const on left: Đặt hằng số bên trái phép so sánh
- ES.47: Dùng “nullptr” thay vì “0” hay ”NULL”

Ví dụ:
```cpp
#include <iostream>
#include <memory>

int main() {
    // ES.45: Dùng hằng số thay magic numbers
    constexpr int MAX_RETRIES = 3;
    constexpr int MIN_PASSWORD_LENGTH = 6;
    constexpr int ADMIN_ID = 42;

    // ES.47: Dùng nullptr thay vì NULL/0
    std::unique_ptr<int> ptr = nullptr;

    // Const on left: hằng số bên trái phép so sánh
    if (nullptr == ptr) {
        ptr = std::make_unique<int>(ADMIN_ID);
    }

    int userInput;
    std::cout << "Nhập mật khẩu mới: ";
    std::cin >> userInput;

    // ES.45 + Const on left
    if (MIN_PASSWORD_LENGTH <= userInput) {
        std::cout << "Mật khẩu hợp lệ!\n";
    } else {
        std::cout << "Mật khẩu phải có ít nhất " 
                  << MIN_PASSWORD_LENGTH << " ký tự\n";
    }

    // Const on left
    if (ADMIN_ID == *ptr) {
        std::cout << "Xin chào Admin!\n";
    }

    return 0;
}
```
Biểu thức & Toán tử (ES)
- ES.41: Dùng ngoặc đơn khi nghi ngờ độ ưu tiên
- ES.43: Tránh biểu thức có thứ tự tính không xác định
- ES.87: Không thêm “== true” hay ”!= false” thừa

Ví dụ:
```cpp
#include <iostream>
#include <vector>

int main() {
    // ES.41: Dùng ngoặc đơn khi nghi ngờ độ ưu tiên
    int a = 5, b = 3, c = 2;
    int result = (a + b) * c;  // Rõ ràng về thứ tự tính toán
    std::cout << "Kết quả: " << result << "\n";

    // ES.43: Tránh biểu thức có thứ tự tính không xác định
    int j = 0;
    nums[j] = j + 10;    //Đảm bảo thứ tự rõ ràng
    j++;

    // ES.87: Không thêm == true/!= false thừa
    bool isValid = true;
    if (isValid) {       //Tốt - không dùng (isValid == true)
        std::cout << "Dữ liệu hợp lệ\n";
    }

    if (!isValid) {      //Tốt - không dùng (isValid == false)
        std::cout << "Dữ liệu không hợp lệ\n";
    }

    return 0;
}
```
I/O & Hiệu suất (SL)
- SL.io.50: Tránh “std::endl” (gọi flush không cần thiết)

Ví dụ:
```cpp
#include <iostream>
#include <fstream>

int main() {
    //Cách viết tốt - dùng '\n' thay vì std::endl
    std::ofstream file("output.txt");  // Mở file để ghi
    
    // Ghi 5 dòng vào file
    for (int i = 1; i <= 5; ++i) {
        file << "This is line " << i << '\n';  // Chỉ xuống dòng, không flush
    }
    
    // Chỉ flush khi thực sự cần thiết
    file.flush();  // Đẩy dữ liệu từ bộ đệm xuống file
    
    // Ví dụ xuất ra console
    std::cout << "Operation completed successfully.\n";  // Không dùng std::endl
    
    return 0;
}
```


### Đảm bảo chất lượng
Thực hiện Mock test với các chức năng đã được sử dụng

\- Trước khi kiểm thử thực hiện tách phần Logic và UI để đảm bảo độ ổn định cao và dễ dàng trong quá trình kiểm thử chức năng.

\- Kiểm thử các lớp và hàm liên quan đến SqlUserRepository

Thực hiện kiểm thử thủ công bằng cách tạo ra các lớp kiểm thử kế thừa lớp “UserRepository” mô phỏng lại các hàm đã sử dụng (**deleteUser**, **updateUser**, **getUserByEmail,** **userExists, deleteUser**) mà không làm ảnh hưởng đến cơ sở dữ liệu.

\-AuthService:

Lớp kiểm thử MockUserRepository:
```cpp
class MockUserRepository : public UserRepository {

public:

QMap&lt;QString, User&gt; users;

bool addUser(const User& user) override {
   if (users.contains(user.email())) {
      return false;
   }
   users.insert(user.email(), user);
   return true;
}

QSharedPointer&lt;User&gt; getUserByEmail(const QString& email) override {
   if (users.contains(email)) {
   return QSharedPointer&lt;User&gt;::create(users.value(email));
   }
   return nullptr;
}

QList&lt;User&gt; getAllUsers() override {
   return users.values(); 
}

bool updateUser(const User& user) override {
   if (!users.contains(user.email())) {
   return false;
   }
   users.insert(user.email(), user);
   return true;
}

bool deleteUser(const QString& email) override {
   return users.remove(email) > 0;
}

bool userExists(const QString& email) override {
   return users.contains(email);
   }
};
```
Dựa trên lớp kiểm thử MockUserRepository ta thu được kết quả với các hàm đã được dùng với UserService:

| STT | Hàm kiểm thử | Trường hợp | Kết quả trả về | Kết quả kiểm thử |
| --- | --- | --- | --- | --- |
| 1   | getUserByEmail(email) | Email tồn tại | Thực thi thành công | PASS |
| 2   | getUserByEmail(email) | Email không tồn tại | Thông báo không tìm thấy tài khoảng | PASS |
| 3   | updateUser(email, newData) | Email tồn tại – Cập nhật toàn bộ thông tin | Cập nhật thành công | PASS |
| 4   | updateUser(email, newData) | Email tồn tại – Cập nhật một phần thông tin | Cập nhật thành công | PASS |
| 5   | updateUser(email, newData) | Email không tồn tại | Cập nhật thất bại | PASS |

Dựa trên lớp kiểm thử MockUserRepository ta thu được kết quả với các hàm đã được dùng với AuthService:

| STT | Hàm kiểm thử | Trường hợp | Kết quả trả về | Kết quả kiểm thử |
| --- | --- | --- | --- | --- |
| 1   | login(email, password) bao gồm userExists và addUser | Đăng nhập hợp lệ | Thực thi thành công | PASS |
| 2   | login(email, password) bao gồm userExists và addUser | Sai mật khẩu | Thông báo sai thông tin đăng nhập | PASS |
| 3   | login(email, password) bao gồm userExists và addUser | Email không tồn tại | Thông báo sai thông tin đăng nhập | PASS |
| 4   | signup(email, password, name) | Đăng ký hợp lệ | Thực thi thành công | PASS |
| 5   | signup(email, password, name) | Email không hợp lệ | Thông báo đăng ký không thành công | PASS |

Đánh giá kiểm thử các lớp và hàm liên quan đên UserRepository

- Tổng số test case: 10
- Số lượng test case thành công: 10
- Số lượng test case thất bại: 0
- Tỷ lệ thành công: 100%

→ Các test case thành công cho thấy các chức năng hoạt động đúng như mong đợi.

\- Kiểm thử các lớp và hàm liên quan đến TripRepository

Thực hiện kiểm thử thủ công bằng cách tạo ra các lớp kiểm thử kế thừa lớp “TripRepository” mô phỏng lại các hàm đã sử dụng (**getAllTrips**, **getTripById**, **addTrip,** **updateTrip, deleteTrip**) mà không làm ảnh hưởng đến cơ sở dữ liệu.

Lớp kiểm thử TripRepository:
```cpp
class MockTripRepository : public TripRepository {

public:

QList&lt;Trip&gt; trips;

bool shouldFail = false;

QList&lt;Trip&gt; getAllTrips() override {
   if (shouldFail) {
   throw std::runtime_error("Mock database error");
   }
   return trips;
}

Trip getTripById(int tripId) override {
   for (const Trip& trip : trips) {
      if (trip.getTripId() == tripId) {
         return trip;
      }
   }
   return Trip();
}

bool addTrip(const Trip& trip) override {
   if (shouldFail) {
      return false;
   }
   trips.append(trip);
   return true;
}

bool updateTrip(const Trip& trip) override {
   if (shouldFail) {
      return false;
   }
   for (int i = 0; i < trips.size(); ++i) {
      if (trips\[i\].getTripId() == trip.getTripId()) {
      trips\[i\] = trip;
      return true;
      }
   }
   return false;
}

bool deleteTrip(int tripId) override {
   if (shouldFail) {
      return false;
   }
   for (int i = 0; i < trips.size(); ++i) {
      if (trips\[i\].getTripId() == tripId) {
      trips.removeAt(i);
      return true;
      }
   }
   return false;
   }
};
```

Dựa trên lớp kiểm thử TripRepository ta thu được kết quả với các hàm đã được dùng với TripService

| STT | Hàm kiểm thử | Trường hợp | Kết quả trả về | Kết quả kiểm thử |
| --- | --- | --- | --- | --- |
| 1   | createTrip(trip) | Nhập thông tin hợp lệ | Thực thi thành công | PASS |
| 2   | createTrip(trip) | Nhập thông tin không hợp lệ | Thông báo thuộc tính lỗi | PASS |
| 3   | createTrip(trip) | Thông tin trùng lặp | Thông báo trùng lặp | PASS |
| 4   | getAllTrips() | Không | Toàn bộ thông tin các Trip | PASS |

Đánh giá kiểm thử các lớp và hàm liên quan đên TripRepository

- Tổng số test case: 4
- Số lượng test case thành công: 4
- Số lượng test case thất bại: 0
- Tỷ lệ thành công: 100%

→ Các test case thành công cho thấy các chức năng hoạt động đúng như mong đợi.

Kết luận: Các chức năng đã được sử dụng hoạt động đúng theo yêu cầu, đảm bảo tính chính xác.

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

```

```
