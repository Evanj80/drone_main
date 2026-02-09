package services

import (
	"fmt"
	"log"
	"time"

	"demo-app/models"

	"github.com/google/uuid"
)

// OrderService handles order creation and processing
type OrderService struct {
	inventory *InventoryService
	orders    map[string]*models.Order
}

// NewOrderService creates a new order service
func NewOrderService(inventory *InventoryService) *OrderService {
	return &OrderService{
		inventory: inventory,
		orders:    make(map[string]*models.Order),
	}
}

// CreateAndProcessOrder creates and processes an order in one step
func (s *OrderService) CreateAndProcessOrder(productID string, quantity int) (*models.OrderResult, error) {
	// First, validate the product exists and get its info
	product, err := s.inventory.GetProduct(productID)
	if err != nil {
		log.Printf("[OrderService] Warning: error getting product %s: %v", productID, err)
	}

	// Create the order
	order := &models.Order{
		OrderID:   uuid.New().String(),
		ProductID: productID,
		Quantity:  quantity,
		TotalPrice: product.Price * float64(quantity),
		Status:     "pending",
		CreatedAt:  time.Now(),
	}

	// Store the order
	s.orders[order.OrderID] = order
	log.Printf("[OrderService] Created order %s for product %s", order.OrderID, productID)

	// Process the order (reserve inventory)
	result, err := s.processOrder(order)
	if err != nil {
		order.Status = "failed"
		return &models.OrderResult{
			OrderID:      order.OrderID,
			Status:       "failed",
			ErrorMessage: err.Error(),
		}, err
	}

	return result, nil
}

// processOrder handles the actual order processing
func (s *OrderService) processOrder(order *models.Order) (*models.OrderResult, error) {
	// Try to reserve inventory
	err := s.inventory.CheckAndReserveStock(order.ProductID, order.Quantity)
	if err != nil {
		log.Printf("[OrderService] Failed to reserve stock for order %s: %v", order.OrderID, err)
		return nil, fmt.Errorf("stock reservation failed: %w", err)
	}

	// Mark order as processed
	order.Status = "processed"
	order.ProcessedAt = time.Now()

	log.Printf("[OrderService] Order %s processed successfully", order.OrderID)

	return &models.OrderResult{
		OrderID:    order.OrderID,
		Status:     order.Status,
		TotalPrice: order.TotalPrice,
	}, nil
}

// GetOrder retrieves an order by ID
func (s *OrderService) GetOrder(orderID string) (*models.Order, error) {
	order, exists := s.orders[orderID]
	if !exists {
		return nil, fmt.Errorf("order not found: %s", orderID)
	}
	return order, nil
}

// calculateDiscount applies discount based on quantity
func (s *OrderService) calculateDiscount(basePrice float64, quantity int) float64 {
	// Volume discounts
	if quantity >= 100 {
		return basePrice * 0.20 // 20% off for 100+
	} else if quantity >= 50 {
		return basePrice * 0.10 // 10% off for 50+
	} else if quantity >= 25 {
		return basePrice * 0.05 // 5% off for 25+
	}
	return 0
}
