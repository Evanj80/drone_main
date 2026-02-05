"""
User model
"""
from dataclasses import dataclass
from typing import Optional


@dataclass
class User:
    """Represents a user in the system"""
    id: str
    username: str
    email: str
    tier: str = "free"  # free, premium, enterprise
    bio: Optional[str] = None

    def to_dict(self) -> dict:
        return {
            "id": self.id,
            "username": self.username,
            "email": self.email,
            "tier": self.tier,
            "bio": self.bio
        }
