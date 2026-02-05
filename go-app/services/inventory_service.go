package services

import (
	"errors"
	"log"
	"sync"

	"demo-app/models"
)

var (
	ErrProductNotFound    = errors.New("product not found")
	ErrInsufficientStock  = errors.New("insufficient stock")
	ErrProductUnavailable = errors.New("product is no longer available")
)

// InventoryService manages product inventory
type InventoryService struct {
	products map[string]*models.Product
	mu       sync.RWMutex
}

// NewInventoryService creates a new inventory service with sample data
func NewInventoryService() *InventoryService {
	svc := &InventoryService{
		products: make(map[string]*models.Product),
	}
	svc.loadSampleData()
	return svc
}

func (s *InventoryService) loadSampleData() {
	sampleProducts := []*models.Product{
		{ID: "PROD-001", Name: "Widget A", Price: 29.99, StockLevel: 100, IsAvailable: true},
		{ID: "PROD-002", Name: "Widget B", Price: 49.99, StockLevel: 50, IsAvailable: true},
		{ID: "PROD-003", Name: "Gadget X", Price: 99.99, StockLevel: 25, IsAvailable: true},
		{ID: "PROD-LIMITED", Name: "Limited Edition", Price: 199.99, StockLevel: 5, IsAvailable: true},
		// PROD-DISCONTINUED exists in old orders but is no longer available
		{ID: "PROD-DISCONTINUED", Name: "Old Product", Price: 19.99, StockLevel: 0, IsAvailable: false},
	}

	for _, p := range sampleProducts {
		s.products[p.ID] = p
	}
}

// GetProduct retrieves a product by ID
// Returns the product and any error encountered
func (s *InventoryService) GetProduct(productID string) (*models.Product, error) {
	s.mu.RLock()
	defer s.mu.RUnlock()

	product, exists := s.products[productID]
	if !exists {
		log.Printf("[Inventory] Product not found: %s", productID)
		return nil, ErrProductNotFound
	}

	// BUG: We check availability but still return nil for unavailable products
	// The error is returned but the nil product is not handled properly by callers
	if !product.IsAvailable {
		log.Printf("[Inventory] Product %s is discontinued/unavailable", productID)
		return nil, ErrProductUnavailable // Returns nil product with error
	}

	return product, nil
}

// CheckAndReserveStock checks if sufficient stock exists and reserves it
func (s *InventoryService) CheckAndReserveStock(productID string, quantity int) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	product, exists := s.products[productID]
	if !exists {
		return ErrProductNotFound
	}

	if !product.IsAvailable {
		return ErrProductUnavailable
	}

	if product.StockLevel < quantity {
		log.Printf("[Inventory] Insufficient stock for %s: have %d, need %d",
			productID, product.StockLevel, quantity)
		return ErrInsufficientStock
	}

	// Reserve stock
	product.StockLevel -= quantity
	log.Printf("[Inventory] Reserved %d units of %s (remaining: %d)",
		quantity, productID, product.StockLevel)

	return nil
}

// GetStockLevel returns current stock level for a product
func (s *InventoryService) GetStockLevel(productID string) (int, error) {
	s.mu.RLock()
	defer s.mu.RUnlock()

	product, exists := s.products[productID]
	if !exists {
		return 0, ErrProductNotFound
	}

	return product.StockLevel, nil
}
