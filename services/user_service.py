"""
User Service - handles user data retrieval
"""
import logging
from typing import Optional
from models.user import User
from data.user_cache import UserCache

logger = logging.getLogger(__name__)


class UserService:
    """Service for managing user data"""

    def __init__(self):
        self.cache = UserCache()
        self._load_sample_users()

    def _load_sample_users(self):
        """Load sample users into cache"""
        sample_users = [
            User(id="user_001", username="alice", email="alice@example.com", tier="premium"),
            User(id="user_002", username="bob", email="bob@example.com", tier="free"),
            User(id="user_003", username="charlie", email="charlie@example.com", tier="premium"),
        ]
        for user in sample_users:
            self.cache.set(user.id, user)

    def get_user(self, user_id: str) -> Optional[User]:
        """
        Retrieve a user by ID.

        Note: Returns None for guest/temporary users - this is intentional
        as guest users don't have persistent profiles.
        """
        logger.info(f"Looking up user: {user_id}")

        # Check cache first
        cached = self.cache.get(user_id)
        if cached:
            logger.info(f"Found user {user_id} in cache")
            return cached

        # Guest users don't have persistent records
        if user_id.startswith("guest_") or user_id.startswith("temp_"):
            logger.info(f"Guest/temp user {user_id} - no persistent profile")
            return None  # BUG: Callers need to handle this None case!

        # Try to fetch from "database" (simulated)
        user = self._fetch_from_db(user_id)
        if user:
            self.cache.set(user_id, user)

        return user

    def _fetch_from_db(self, user_id: str) -> Optional[User]:
        """Simulate database fetch"""
        # In real app, this would query a database
        logger.info(f"DB lookup for user: {user_id}")
        return None  # User not found in DB

    def get_user_tier(self, user_id: str) -> str:
        """Get the subscription tier for a user"""
        user = self.get_user(user_id)
        if user:
            return user.tier
        return "free"  # Default tier for unknown users
