//调聚光灯方向和位置的

//case 'a': // 移动light2
//	spot_pos[0] -= 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//	break;
//case 'd':// 右102
//	spot_pos[0] += 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//	break;
//case 'w':// 上101
//	spot_pos[1] -= 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//	break;
//case 's':// 下103
//	spot_pos[1] += 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//	break;
//case 'q':// 上101
//	spot_pos[2] -= 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//	break;
//case 'e':// 下103
//	spot_pos[2] += 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//	break;
//
//case 'j': // 移动light2
//	spot_direction[0] -= 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//	break;
//case 'l':// 右102
//	spot_direction[0] += 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//	break;
//case 'i':// 上101
//	spot_direction[1] -= 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//	break;
//case 'k':// 下103
//	spot_direction[1] += 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//	break;
//case 'u':// 上101
//	spot_direction[2] -= 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//	break;
//case 'o':// 下103
//	spot_direction[2] += 0.5f;
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_direction);
//	cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//	break;

//调书的位置和轨迹的

//case 'a': // 左100
	//	bookTranslateX -= bookMove;
	//	cout << bookTranslateX << ", " << bookTranslateY << endl;
	//	break;
	//case 'd':// 右102
	//	bookTranslateX += bookMove; cout << bookTranslateX << ", " << bookTranslateY << endl;
	//	break;
	//case 'w':// 上101
	//	bookTranslateY += bookMove; cout << bookTranslateX << ", " << bookTranslateY << endl;
	//	break;
	//case 's':// 下103
	//	bookTranslateY -= bookMove; cout << bookTranslateX << ", " << bookTranslateY << endl;
	//	break;
	//case 'q':// 上101
	//	bookRotate += bookRotateV; cout << bookRotate << endl;
	//	break;
	//case 'e':// 下103
	//	bookRotate -= bookRotateV; cout << bookRotate << endl;
	//	break;
	//case '1':
	//	fcStart -= fcSEChangeV;
	//	cout << fcStart << "  " << fcEnd << endl;
	//	glFogf(GL_FOG_START, fcStart);
	//	glFogf(GL_FOG_END, fcEnd);
	//	break;
	//case '2':
	//	fcStart += fcSEChangeV;
	//	cout << fcStart << "  " << fcEnd << endl;
	//	glFogf(GL_FOG_START, fcStart);
	//	glFogf(GL_FOG_END, fcEnd);
	//	break;
	//case '3':
	//	fcEnd -= fcSEChangeV;
	//	cout << fcStart << "  " << fcEnd << endl;
	//	glFogf(GL_FOG_START, fcStart);
	//	glFogf(GL_FOG_END, fcEnd);
	//	break;
	//case '4':
	//	fcEnd += fcSEChangeV;
	//	glFogf(GL_FOG_START, fcStart);
	//	glFogf(GL_FOG_END, fcEnd);
	//	cout << fcStart << "  " << fcEnd << endl;
	//	break;
	//case '5':
	//	fcSEChangeV *= 2;
	//	cout << fcSEChangeV<< endl;
	//	break;
	//case '6':
	//	fcSEChangeV /= 2;
	//	cout << fcSEChangeV<< endl;
	//	break;
	//case '7':
	//	bookMove += 0.1f;
	//	cout << bookMove << endl;
	//	break;
	//case '8':
	//	bookMove -= 0.1f;
	//	cout << bookMove << endl;
	//	break;
	//case '9':
	//	bookCoverScale *= 10;
	//	cout << bookCoverScale << endl;
	//	break;
	//case '0':
	//	bookCoverScale *= 0.1f;
	//	cout << bookCoverScale << endl;
	//	break;
	//case '-':
	//	bookRotateV *= 0.1f;
	//	cout << bookRotateV << endl;
	//	break;
	//case '=':
	//	bookRotateV *= 10.0f;
	//	cout << bookRotateV << endl;
	//	break;
	//case 'j': // 左100
	//	bookCoverScaleX -= bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
	//	break;
	//case 'l':// 右102
	//	bookCoverScaleX += bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
	//	break;
	//case 'i':// 上101
	//	bookCoverScaleY += bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
	//	break;
	//case 'k':// 下103
	//	bookCoverScaleY -= bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
	//	break;
	//case '.':
	//	bookPosCounter++;
	//	cout << bookPos <<"; "<<bookPath->getX(bookPos) << ", " << bookPath->getY(bookPos) <<", "<< int((bookPos* posPerAngle + bookPosCounter) * 1.5f)%360  << endl;
	//	break;

//调buddha的光照

//case 'a': // 移动light2
//	mat_diffuse[0] -= 0.1f;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//case 'd':// 右102
//	mat_diffuse[0] += 0.1f;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//case 'w':// 上101
//	mat_diffuse[1] -= 0.1f;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//case 's':// 下103
//	mat_diffuse[1] += 0.1f;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//case 'q':// 上101
//	mat_diffuse[2] -= 0.1f;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//case 'e':// 下103
//	mat_diffuse[2] += 0.1f;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//
//case 'f': // 移动light2
//	mat_color[0] -= 0.1f;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 'h':// 右102
//	mat_color[0] += 0.1f;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 't':// 上101
//	mat_color[1] -= 0.1f;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 'g':// 下103
//	mat_color[1] += 0.1f;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 'r':// 上101
//	mat_color[2] -= 0.1f;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 'y':// 下103
//	mat_color[2] += 0.1f;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//
//case 'j': // 移动light2
//	mat_emission[0] -= 0.1f;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'l':// 右102
//	mat_emission[0] += 0.1f;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'i':// 上101
//	mat_emission[1] -= 0.1f;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'k':// 下103
//	mat_emission[1] += 0.1f;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'u':// 上101
//	mat_emission[2] -= 0.1f;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'o':// 下103
//	mat_emission[2] += 0.1f;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'z':// 下103
//	mat_diffuse[0] = mat_diffuse[1] = mat_diffuse[2] = 0;
//	cout << "mat_diffuse: " << mat_diffuse[0] << ", " << mat_diffuse[1] << ", " << mat_diffuse[2] << ", " << endl;
//	break;
//case 'x':// 下103
//	mat_color[0] = mat_color[1] = mat_color[2] = 0;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 'c':// 下103
//	mat_emission[0] = mat_emission[1] = mat_emission[2] = 0;
//	cout << "mat_emission: " << mat_emission[0] << ", " << mat_emission[1] << ", " << mat_emission[2] << ", " << endl;
//	break;
//case 'm':
//	cin >> mat_color[0] >> mat_color[1] >> mat_color[2];
//	mat_color[0] /= 255;
//	mat_color[1] /= 255;
//	mat_color[2] /= 255;
//	cout << "mat_color: " << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", " << endl;
//	break;
//case 'n':
//	for (int i = 0; i < 3; i++)
//	{
//		mat_color[i] *= 1.02f;
//	}
//	cout << "{" << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", 1.0f }," << endl;
//	break;
//case 'b':
//	for (int i = 0; i < 3; i++)
//	{
//		mat_color[i] /= 1.01f;
//	}
//	cout << "{" << mat_color[0] << ", " << mat_color[1] << ", " << mat_color[2] << ", 1.0f }," << endl;
//	break;