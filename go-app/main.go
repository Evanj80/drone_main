package main

import (
	"encoding/json"
	"log"
	"math/rand"
	"net/http"
	"os"
	"time"

	"demo-app/handlers"
	"demo-app/services"
)

func main() {
	log.Println("Starting Order Processing Service...")

	// Initialize services
	inventoryService := services.NewInventoryService()
	orderService := services.NewOrderService(inventoryService)
	handler := handlers.NewOrderHandler(orderService)

	// Set up routes
	http.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
		json.NewEncoder(w).Encode(map[string]string{"status": "healthy"})
	})
	http.HandleFunc("/api/orders", handler.CreateOrder)
	http.HandleFunc("/api/orders/process", handler.ProcessOrder)

	// Start background order processor that will trigger the bug
	go startBackgroundProcessor(orderService)

	port := os.Getenv("PORT")
	if port == "" {
		port = "8080"
	}

	log.Printf("Server listening on port %s", port)
	if err := http.ListenAndServe(":"+port, nil); err != nil {
		log.Fatalf("Server failed: %v", err)
	}
}

func startBackgroundProcessor(orderService *services.OrderService) {
	time.Sleep(15 * time.Second) // Wait for app to initialize

	testOrders := []struct {
		productID string
		quantity  int
	}{
		{"PROD-001", 5},
		{"PROD-002", 3},
		{"PROD-DISCONTINUED", 10},
		{"PROD-003", 2},
		{"PROD-LIMITED", 100},

	for {
		// Randomly pick an order to process
		order := testOrders[rand.Intn(len(testOrders))]
		log.Printf("Background processor: creating order for %s (qty: %d)", order.productID, order.quantity)

		result, err := orderService.CreateAndProcessOrder(order.productID, order.quantity)
		if err != nil {
			log.Printf("Order processing error: %v", err)
			// Continue processing other orders on error
			time.Sleep(3 * time.Second)
			continue
		}

		log.Printf("Order processed successfully: %s -> status: %s", result.OrderID, result.Status)
		time.Sleep(5 * time.Second)
	}
}
