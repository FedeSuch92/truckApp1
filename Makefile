.PHONY: clean All

All:
	@echo "----------Building project:[ UOCTransport - Test ]----------"
	@"$(MAKE)" -f  "UOCTransport.mk"
clean:
	@echo "----------Cleaning project:[ UOCTransport - Test ]----------"
	@"$(MAKE)" -f  "UOCTransport.mk" clean
