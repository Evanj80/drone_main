        user = self.user_service.get_user(user_id)

        if user is None:
            logger.warning(f"User not found for user_id: {user_id}. Returning None.")
            return None

        # Build the enriched profile
        profile = EnrichedProfile(
            user_id=user_id,
            username=user.username,
            email=user.email,
            display_name=self._compute_display_name(user),
            tier=user.tier,
            profile_completeness=self._calculate_completeness(user),
            preferences=self._get_preferences(user_id)
        )

        logger.info(f"Built enriched profile: {profile.display_name}")