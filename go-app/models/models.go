package models

import "time"

// Product represents an item in inventory
type Product struct {
	ID          string  `json:"id"`
	Name        string  `json:"name"`
	Price       float64 `json:"price"`
	StockLevel  int     `json:"stock_level"`
	IsAvailable bool    `json:"is_available"`
}

// Order represents a customer order
type Order struct {
	OrderID     string    `json:"order_id"`
	ProductID   string    `json:"product_id"`
	Quantity    int       `json:"quantity"`
	TotalPrice  float64   `json:"total_price"`
	Status      string    `json:"status"`
	CreatedAt   time.Time `json:"created_at"`
	ProcessedAt time.Time `json:"processed_at,omitempty"`
}

// OrderResult contains the result of order processing
type OrderResult struct {
	OrderID      string  `json:"order_id"`
	Status       string  `json:"status"`
	TotalPrice   float64 `json:"total_price"`
	ErrorMessage string  `json:"error_message,omitempty"`
}
