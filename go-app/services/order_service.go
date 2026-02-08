    product, err := s.inventory.GetProduct(productID)
    if err != nil {
        log.Printf("[OrderService] Warning: error getting product %s: %v", productID, err)
        return nil, fmt.Errorf("product validation failed: %w", err)
    }