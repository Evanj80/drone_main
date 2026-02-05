"""
Demo Python Application - User Profile Service
This application has a bug that causes crashes under certain conditions.
"""
import os
import time
import logging
from flask import Flask, jsonify, request
from services.user_service import UserService
from services.profile_service import ProfileService

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = Flask(__name__)

# Initialize services
user_service = UserService()
profile_service = ProfileService(user_service)


@app.route('/health', methods=['GET'])
def health():
    return jsonify({"status": "healthy"})


@app.route('/api/users/<user_id>/profile', methods=['GET'])
def get_user_profile(user_id):
    """Get user profile with enriched data"""
    logger.info(f"Fetching profile for user: {user_id}")

    # This call chain will crash for certain user IDs
    enriched_profile = profile_service.get_enriched_profile(user_id)

    return jsonify({
        "user_id": user_id,
        "profile": enriched_profile.to_dict(),
        "timestamp": time.time()
    })


@app.route('/api/users/<user_id>/settings', methods=['GET'])
def get_user_settings(user_id):
    """Get user settings - triggers the bug path"""
    logger.info(f"Fetching settings for user: {user_id}")

    # Get user preferences which also triggers profile fetch
    settings = profile_service.get_user_settings(user_id)

    return jsonify({
        "user_id": user_id,
        "settings": settings,
        "timestamp": time.time()
    })


def trigger_crash_scenario():
    """Background task that periodically triggers the buggy code path"""
    import threading
    import random

    def crash_loop():
        time.sleep(10)  # Wait for app to start
        test_user_ids = ["user_001", "user_002", "guest_temp", "user_003", "cached_user"]

        while True:
            user_id = random.choice(test_user_ids)
            logger.info(f"Background task: checking profile for {user_id}")
            try:
                # This will eventually hit a user that causes a crash
                profile = profile_service.get_enriched_profile(user_id)
                logger.info(f"Profile fetched: {profile.display_name if profile else 'None'}")
            except Exception as e:
                logger.error(f"Crash triggered for user {user_id}: {e}")
                # Print full traceback to stderr for pod logs
                import traceback
                traceback.print_exc()
                # Force process exit to trigger pod restart
                os._exit(1)

            time.sleep(5)

    thread = threading.Thread(target=crash_loop, daemon=False)
    thread.start()


if __name__ == '__main__':
    # Start background crash scenario
    trigger_crash_scenario()

    port = int(os.environ.get('PORT', 8080))
    app.run(host='0.0.0.0', port=port, debug=False)
