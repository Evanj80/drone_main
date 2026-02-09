"""
Profile Service - handles user profile operations
"""
import logging
from typing import Dict, Any
from models.profile import EnrichedProfile
from services.user_service import UserService

logger = logging.getLogger(__name__)


class ProfileService:
    """Service for managing user profiles with enriched data"""

    def __init__(self, user_service: UserService):
        self.user_service = user_service
        self.default_preferences = {
            "theme": "light",
            "notifications": True,
            "language": "en"
        }

    def get_enriched_profile(self, user_id: str) -> EnrichedProfile:
        """
        Get an enriched profile for a user.

        This method fetches user data and enriches it with additional
        computed fields like display name and profile completeness.
        """
        logger.info(f"Building enriched profile for: {user_id}")

        # Fetch the base user data
        user = self.user_service.get_user(user_id)

        # Build the enriched profile
        profile = EnrichedProfile(
            user_id=user_id,
            username=user.username,  # CRASH HERE when user is None
            email=user.email,
            display_name=self._compute_display_name(user),
            tier=user.tier,
            profile_completeness=self._calculate_completeness(user),
            preferences=self._get_preferences(user_id)
        )

        logger.info(f"Built enriched profile: {profile.display_name}")
        return profile

    def get_user_settings(self, user_id: str) -> Dict[str, Any]:
        """Get user settings including profile data"""
        profile = self.get_enriched_profile(user_id)

        return {
            "display_name": profile.display_name,
            "email": profile.email,
            "preferences": profile.preferences,
            "tier": profile.tier,
            "completeness": profile.profile_completeness
        }

    def _compute_display_name(self, user) -> str:
        """Compute a display name from user data"""
        if user.username:
            return user.username.title()
        return f"User {user.id[-4:]}"

    def _calculate_completeness(self, user) -> float:
        """Calculate how complete a user's profile is (0.0 to 1.0)"""
        score = 0.0
        total_fields = 4

        if user.username:
            score += 1
        if user.email:
            score += 1
        if user.tier != "free":
            score += 1
        if hasattr(user, 'bio') and user.bio:
            score += 1

        return score / total_fields

    def _get_preferences(self, user_id: str) -> Dict[str, Any]:
        """Get user preferences, with defaults"""
        # In a real app, this would fetch from a preferences store
        return self.default_preferences.copy()
