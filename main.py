                profile = profile_service.get_enriched_profile(user_id)
                if profile is None:
                    logger.warning(f"No profile found for user {user_id}")
                else:
                    logger.info(f"Profile fetched: {profile.display_name}")