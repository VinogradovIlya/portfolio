from fastapi.testclient import TestClient


class TestPayments:
    """Тесты платежей"""

    def test_create_external_payment_success(self, client: TestClient, funded_user: dict):
        """Тест создания внешнего платежа"""
        payment_data = {
            "amount": 150.75,
            "description": "Test external payment",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        response = client.post("/payments/", json=payment_data, headers=funded_user["headers"])

        assert response.status_code == 200
        data = response.json()

        assert data["amount"] == "150.75"
        assert data["description"] == payment_data["description"]
        assert data["card_last_four"] == payment_data["card_last_four"]
        assert data["card_holder_name"] == payment_data["card_holder_name"]
        assert data["status"] == "created"
        assert data["sender_id"] == funded_user["user"]["id"]
        assert data["receiver_id"] is None
        assert "id" in data
        assert "created_at" in data

    def test_create_internal_payment_success(
        self, client: TestClient, funded_user: dict, second_user: dict
    ):
        """Тест создания внутреннего перевода"""
        payment_data = {
            "amount": 75.50,
            "description": "Internal transfer",
            "receiver_id": second_user["user"]["id"],
        }

        response = client.post("/payments/", json=payment_data, headers=funded_user["headers"])

        assert response.status_code == 200
        data = response.json()

        assert data["amount"] == "75.50"
        assert data["receiver_id"] == second_user["user"]["id"]
        assert data["sender_id"] == funded_user["user"]["id"]
        assert data["status"] == "created"
        assert data["card_last_four"] is None
        assert data["card_holder_name"] is None

    def test_create_payment_insufficient_funds(self, client: TestClient, authenticated_user: dict):
        """Тест создания платежа при недостатке средств"""
        payment_data = {
            "amount": 2000.00,
            "description": "Should fail",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        response = client.post(
            "/payments/", json=payment_data, headers=authenticated_user["headers"]
        )

        assert response.status_code == 400
        assert "Недостаточно средств" in response.json()["detail"]

    def test_create_payment_to_self(self, client: TestClient, funded_user: dict):
        """Тест создания перевода самому себе"""
        payment_data = {
            "amount": 50.00,
            "description": "Self transfer",
            "receiver_id": funded_user["user"]["id"],
        }

        response = client.post("/payments/", json=payment_data, headers=funded_user["headers"])

        assert response.status_code == 400
        assert "самому себе" in response.json()["detail"]

    def test_create_payment_without_auth(self, client: TestClient):
        """Тест создания платежа без авторизации"""
        payment_data = {
            "amount": 50.00,
            "description": "Unauthorized payment",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        response = client.post("/payments/", json=payment_data)
        assert response.status_code == 403

    def test_confirm_external_payment_success(self, client: TestClient, funded_user: dict):
        """Тест подтверждения внешнего платежа"""
        payment_data = {
            "amount": 100.00,
            "description": "Test payment to confirm",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        create_response = client.post(
            "/payments/", json=payment_data, headers=funded_user["headers"]
        )
        payment_id = create_response.json()["id"]

        response = client.put(f"/payments/{payment_id}/confirm", headers=funded_user["headers"])

        assert response.status_code == 200
        data = response.json()
        assert data["status"] == "paid"
        assert data["paid_at"] is not None

        me_response = client.get("/auth/me", headers=funded_user["headers"])
        new_balance = float(me_response.json()["balance"])
        assert new_balance == 900.00

    def test_cancel_payment_success(self, client: TestClient, funded_user: dict):
        """Тест успешной отмены платежа"""
        payment_data = {
            "amount": 75.00,
            "description": "Payment to cancel",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        create_response = client.post(
            "/payments/", json=payment_data, headers=funded_user["headers"]
        )
        payment_id = create_response.json()["id"]

        response = client.put(f"/payments/{payment_id}/cancel", headers=funded_user["headers"])

        assert response.status_code == 200
        data = response.json()
        assert data["status"] == "cancelled"

    def test_get_user_payments_success(self, client: TestClient, funded_user: dict):
        """Тест получения списка платежей пользователя"""
        payments_data = [
            {
                "amount": 100.00,
                "description": "Payment 1",
                "card_last_four": "1111",
                "card_holder_name": "John Doe",
            },
            {
                "amount": 200.00,
                "description": "Payment 2",
                "card_last_four": "2222",
                "card_holder_name": "Jane Smith",
            },
        ]

        for payment_data in payments_data:
            client.post("/payments/", json=payment_data, headers=funded_user["headers"])

        response = client.get("/payments/", headers=funded_user["headers"])

        assert response.status_code == 200
        data = response.json()
        assert len(data) == 2

        for payment in data:
            assert payment["sender_id"] == funded_user["user"]["id"]

    def test_get_payment_by_id_success(self, client: TestClient, funded_user: dict):
        """Тест получения платежа по ID"""
        payment_data = {
            "amount": 125.50,
            "description": "Test payment for retrieval",
            "card_last_four": "5678",
            "card_holder_name": "Jane Doe",
        }

        create_response = client.post(
            "/payments/", json=payment_data, headers=funded_user["headers"]
        )
        payment_id = create_response.json()["id"]

        response = client.get(f"/payments/{payment_id}", headers=funded_user["headers"])

        assert response.status_code == 200
        data = response.json()
        assert data["id"] == payment_id
        assert data["amount"] == "125.50"
        assert data["card_last_four"] == "5678"
        assert data["description"] == payment_data["description"]

    def test_invalid_payment_amount(self, client: TestClient, funded_user: dict):
        """Тест создания платежа с невалидной суммой"""
        payment_data = {
            "amount": -50.00,
            "description": "Invalid amount payment",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        response = client.post("/payments/", json=payment_data, headers=funded_user["headers"])

        assert response.status_code == 422

    def test_confirm_already_paid_payment(self, client: TestClient, funded_user: dict):
        """Тест подтверждения уже оплаченного платежа"""
        payment_data = {
            "amount": 50.00,
            "description": "Test payment",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        create_response = client.post(
            "/payments/", json=payment_data, headers=funded_user["headers"]
        )
        payment_id = create_response.json()["id"]

        response1 = client.put(f"/payments/{payment_id}/confirm", headers=funded_user["headers"])
        assert response1.status_code == 200

        response2 = client.put(f"/payments/{payment_id}/confirm", headers=funded_user["headers"])
        assert response2.status_code == 400
        assert "уже обработан" in response2.json()["detail"]

    def test_get_payment_access_denied(
        self, client: TestClient, funded_user: dict, second_user: dict
    ):
        """Тест получения чужого платежа"""
        payment_data = {
            "amount": 50.00,
            "description": "Private payment",
            "card_last_four": "1234",
            "card_holder_name": "John Doe",
        }

        create_response = client.post(
            "/payments/", json=payment_data, headers=funded_user["headers"]
        )
        payment_id = create_response.json()["id"]

        response = client.get(f"/payments/{payment_id}", headers=second_user["headers"])

        assert response.status_code == 403
        assert "нет доступа" in response.json()["detail"]
