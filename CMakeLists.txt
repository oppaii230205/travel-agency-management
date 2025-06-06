cmake_minimum_required(VERSION 3.16)

project(TravelAgencyGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql Network)

set(TS_FILES TravelAgencyGUI_vi_VN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TravelAgencyGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        DatabaseManager.h
        DatabaseManager.cpp
        TripService.h
        TripService.cpp
        TripRepository.h
        UserRepository.h
        SqlTripRepository.h
        SqlTripRepository.cpp
        SqlUserRepository.h
        SqlUserRepository.cpp
        Trip.h
        Trip.cpp
        User.h
        User.cpp
        AddTripDialog.h AddTripDialog.cpp AddTripDialog.ui
        AddTripDialog.cpp
        TripListDialog.h TripListDialog.cpp TripListDialog.ui
        loginwindow.h
        loginwindow.cpp login_window.ui
        signupwindow.h signup_window.ui
        signupwindow.cpp
        authservice.h
        authservice.cpp
        UserService.h UserService.cpp
        ShowUserInformationDialog.h ShowUserInformationDialog.cpp ShowUserInformationDialog.ui
        BookingService.h
        Booking.h
        constants.h
        constants.cpp
        Booking.cpp
        BookingRepository.h
        SqlBookingRepository.h
        SqlBookingRepository.cpp
        BookingService.cpp
        Review.h
        Review.cpp
        ReviewRepository.h
        SqlReviewRepository.h
        SqlReviewRepository.cpp
        ReviewService.h
        ReviewService.cpp
        ReviewDialog.ui
        qaesencryption.h
        qaesencryption.cpp
        CrypToUtils.h CrypToUtils.cpp
        TripCard.h TripCard.cpp TripCard.ui
        resources.qrc
        AzureStorageService.h AzureStorageService.cpp
        TripDetailDialog.h TripDetailDialog.cpp TripDetailDialog.ui
        CustomMessageBox.h CustomMessageBox.cpp
        IDataProvider.h
        SqlDao.h
        SqlDao.cpp
        Registry.h
        App.h
        App.cpp
        Event.h
        IObserver.h
        Observable.h
        Observable.cpp
        TripBookedEvent.h
        LoggingObserver.h
        AnalyticsObserver.h
        BaseTripDialog.h
        BaseTripDialog.cpp
        BookedTripCard.h
        BookedTripCard.cpp
        BookedTripsDialog.h
        BookedTripsDialog.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TravelAgencyGUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(TravelAgencyGUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TravelAgencyGUI
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(TravelAgencyGUI PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TravelAgencyGUI)
endif()
set_target_properties(TravelAgencyGUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TravelAgencyGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TravelAgencyGUI)
endif()
