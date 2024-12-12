namespace other {
	Vector3 m_manipulate = Vector3::Zero();
	
	inline void DynamicManipAngles(std::vector<Vector3>& re, float max = 1.5f, float maxy = 1.5f, int numPoints = 100)
	{
		float radius = max; // Radius of the sphere

		for (int i = 0; i < numPoints; ++i) {
			float theta = static_cast<float>((rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
			float phi = static_cast<float>((rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle

			float x = radius * sinf(phi) * cosf(theta);
			float y = maxy * sinf(phi) * sinf(theta);
			float z = radius * cosf(phi);

			re.emplace_back(x, y, z);
			re.emplace_back(-x, -y, -z);
			re.emplace_back(x, 0.f, z);

			re.emplace_back(0.f, y, 0.f);
			re.emplace_back(0.f, -y, 0.f);

			re.emplace_back(-x, 0.f, 0.f);
			re.emplace_back(x, 0.f, 0.f);

			re.emplace_back(0.f, 0.f, z);
			re.emplace_back(0.f, 0.f, -z);
		}
	}

	void find_manipulate_angle() {
		Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);

		Vector3 choice = Vector3::Zero();

		auto* target = target_ply;

		if (utils::LineOfSight(re_p, target_ply->get_bone_pos(head))) {
			m_manipulate = Vector3::Zero();
			return;
		}

		float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
		float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * LocalPlayer::Entity()->MaxVelocity()) - 0.05f;
		float max_v_multicplier = 4.5f;
		float v_mm_max_eye = mm_max_eye / max_v_multicplier;

		auto right = LocalPlayer::Entity()->eyes()->MovementRight();
		auto forward = LocalPlayer::Entity()->eyes()->MovementForward();

		std::vector<Vector3> generatedPoints;
		DynamicManipAngles(generatedPoints, mm_max_eye, 1.5, 300);

		for (auto s : generatedPoints) {
			Vector3 point = re_p + s;

			if (!utils::LineOfSight(point, re_p))
				continue;

			if (!utils::LineOfSight(point, point))
				continue;

			choice = s;
			break;
		}

		if (choice.empty()) {
			m_manipulate = Vector3::Zero();
			return;
		}

		m_manipulate = choice;
	}

	//void find_manipulate_angle() {
	//	auto loco = LocalPlayer::Entity();
	//	Vector3 re_p = loco->transform()->position() + loco->transform()->up() * (PlayerEyes::EyeOffset().y + loco->eyes()->viewOffset().y);
	//	// real eye pos

	//	Vector3 choice = Vector3::Zero();

	//	if (GamePhysics::IsVisible(re_p, target_ply->find_mpv_bone()->position) || !target_ply->isCached()) {
	//		m_manipulate = Vector3::Zero();
	//		return;
	//	}

	//	float desyncTime = (Time::realtimeSinceStartup() - loco->lastSentTickTime()) - 0.03125 * 3;
	//	float mm_max_eye = (1.0f + ((desyncTime + 2.f / 5.f + 0.125f) * 2.5f) * loco->MaxVelocity()) - 0.05f;

	//	std::vector<Vector3> generatedPoints;
	//	DynamicManipAngles(generatedPoints, mm_max_eye, 1.5, 300);

	//	for (auto s : generatedPoints) {
	//		Vector3 point = re_p + s;

	//		if (!GamePhysics::IsVisible(point, re_p))
	//			continue;

	//		if (!GamePhysics::IsVisible(re_p, point))
	//			continue;

	//		choice = s;
	//		break;
	//	}
	//	if (choice.empty()) {
	//		m_manipulate = Vector3::Zero();
	//		return;
	//	}

	//	m_manipulate = choice;
	//}
	void test_bundle(AssetBundle* bundle) {
		if (!bundle) {
			std::cout << "bundle nfound\n";
			return;
		}

		auto arr = bundle->GetAllAssetNames();
		if (!arr) {
			std::cout << "arr nfound\n";
			return;
		}

		for (int j = 0; j < arr->ArraySize(); j++) {
			auto name = arr->GetArray(j);

			printf("%ls\n", name->buffer);
		}

		std::cout << "bundletest - success\n";
	}
}
void dispatch_keybind(KeyCode& s) {

}
//TestFly();
//float num5 = max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
//float num6 = loco.player->GetJumpHeight() + num5;
//Menu::Vars::misc::max_flyhack = num6;
//if (flyhackDistanceVertical <= num6) {
//	vars::fly::flyhack = flyhackDistanceVertical;
//}
//
//float num7 = max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
//float num8 = 5.f + num7;
//vars::misc::max_hor_flyhack = num8;
//if (flyhackDistanceHorizontal <= num8) {
//	vars::fly::hor_flyhack = flyhackDistanceHorizontal;
//}
//if (flyhackDistanceVertical > num6) {
//	loco.player->movement()->groundAngle(Vector3::Zero());
//	loco.player->movement()->groundAngleNew(Vector3::Zero());
//	loco.player->movement()->TargetMovementk__BackingField(Vector3::Zero());
//	loco.player->get_transform()->set_position(loco.player->get_transform()->position() - Vector3(0, 0.3, 0));
//}
//else {}
//
//if (flyhackDistanceHorizontal > num8) {
//	loco.player->movement()->groundAngle(Vector3::Zero());
//	loco.player->movement()->groundAngleNew(Vector3::Zero());
//	loco.player->movement()->TargetMovementk__BackingField(Vector3::Zero());
//	loco.player->get_transform()->set_position(loco.player->get_transform()->position() - Vector3(0, 0.2, 0));
//}
//else {}