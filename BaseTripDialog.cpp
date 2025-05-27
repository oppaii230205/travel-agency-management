#include "BaseTripDialog.h"
#include "TripDetailDialog.h"
#include <QVBoxLayout>
#include <QShowEvent>

BaseTripDialog::BaseTripDialog(QSharedPointer<TripService> tripService,
                               QSharedPointer<BookingService> bookingService,
                               QSharedPointer<ReviewService> reviewService,
                               QWidget *parent)
    : QDialog(parent),
    _tripService(tripService),
    _bookingService(bookingService),
    _reviewService(reviewService),
    _gridLayout(nullptr),
    _scrollArea(nullptr),
    _contentWidget(nullptr),
    _initialized(false)
{
    // Only initialize UI in constructor - NO virtual function calls
    initializeUI();

    // Set the minimum size here so dialog has proper size before being shown
    setMinimumSize(850, 625);
}

void BaseTripDialog::initializeDialog()
{
    if (_initialized) return;

    // Template method implementation - called after construction
    setWindowTitle(getWindowTitle());

    setupAdditionalUI(); // Hook for subclasses
    refreshTripList();
    _initialized = true;
}

void BaseTripDialog::initializeUI()
{
    // Create scroll area
    _scrollArea = new QScrollArea(this);
    _scrollArea->setWidgetResizable(true);

    // Widget containing main content
    _contentWidget = new QWidget();
    _gridLayout = new QGridLayout(_contentWidget);
    _gridLayout->setSpacing(20);
    _gridLayout->setContentsMargins(20, 20, 20, 20);

    _scrollArea->setWidget(_contentWidget);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(_scrollArea);
}

void BaseTripDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // Initialize dialog when it's shown for the first time
    if (!_initialized) {
        initializeDialog();
    }
}

void BaseTripDialog::refreshTripList()
{
    if (!_gridLayout) return; // Safety check

    // Clear old cards safely
    QLayoutItem* item;
    while ((item = _gridLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater(); // Use deleteLater instead of delete
        }
        delete item;
    }

    // Get trips to display (implemented by subclasses)
    QList<Trip> trips = getTripsToDisplay();

    // Add new cards
    for (int i = 0; i < trips.size(); ++i) {
        TripCard *card = createTripCard(trips[i]); // Factory method

        if (!card) continue; // Safety check

        // Common connections
        connect(card, &TripCard::detailsClicked, this, &BaseTripDialog::handleDetailsClicked);

        // Hook for additional setup
        onTripCardCreated(card, trips[i]);

        // Calculate position in grid
        int row = i / 3; // 3 columns
        int col = i % 3;
        _gridLayout->addWidget(card, row, col);
    }
}

void BaseTripDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    arrangeCardsInGrid();
}

void BaseTripDialog::arrangeCardsInGrid()
{
    if (!_gridLayout) return; // Safety check

    // Calculate number of columns based on width
    int cardWidth = 300;
    int spacing = _gridLayout->spacing();
    int margin = _gridLayout->contentsMargins().left() + _gridLayout->contentsMargins().right();

    int availableWidth = width() - margin;
    int columns = qMax(1, availableWidth / (cardWidth + spacing));

    // Rearrange cards
    QList<TripCard*> cards = findChildren<TripCard*>();
    for (int i = 0; i < cards.size(); ++i) {
        int row = i / columns;
        int col = i % columns;
        _gridLayout->addWidget(cards[i], row, col);
    }
}

void BaseTripDialog::handleDetailsClicked(int tripId)
{
    Trip trip = _tripService->getTripById(tripId);
    QSharedPointer<TripDetailDialog> detailsDialog = QSharedPointer<TripDetailDialog>::create(trip, _reviewService);
    detailsDialog->exec();
}
