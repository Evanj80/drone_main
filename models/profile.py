"""
Profile models
"""
from dataclasses import dataclass, field
from typing import Dict, Any


@dataclass
class EnrichedProfile:
    """An enriched user profile with computed fields"""
    user_id: str
    username: str
    email: str
    display_name: str
    tier: str
    profile_completeness: float
    preferences: Dict[str, Any] = field(default_factory=dict)

    def to_dict(self) -> dict:
        return {
            "user_id": self.user_id,
            "username": self.username,
            "email": self.email,
            "display_name": self.display_name,
            "tier": self.tier,
            "profile_completeness": self.profile_completeness,
            "preferences": self.preferences
        }
