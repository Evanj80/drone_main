"""
User cache - simple in-memory cache for user data
"""
import logging
from typing import Optional, Dict, Any

logger = logging.getLogger(__name__)


class UserCache:
    """Simple in-memory cache for user objects"""

    def __init__(self):
        self._cache: Dict[str, Any] = {}

    def get(self, key: str) -> Optional[Any]:
        """Get an item from cache"""
        return self._cache.get(key)

    def set(self, key: str, value: Any) -> None:
        """Set an item in cache"""
        self._cache[key] = value
        logger.debug(f"Cached user: {key}")

    def delete(self, key: str) -> None:
        """Delete an item from cache"""
        if key in self._cache:
            del self._cache[key]

    def clear(self) -> None:
        """Clear the entire cache"""
        self._cache.clear()
