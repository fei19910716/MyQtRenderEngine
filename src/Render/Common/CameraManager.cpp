#include "cameramanager.h"

#include <algorithm>

namespace render {
    const float SENSITIVITY =  0.1f;

    CameraManager *CameraManager::camera = nullptr;

    CameraManager::CameraManager() {
        UpdateViewMatrix();

        ViewDir = eye - target;
        DefaultViewDir = ViewDir;
    }

    void CameraManager::SetRotateXY(float x, float y) {
        rotateX = x;
        rotateY = y;

        QMatrix4x4 rotation;
        rotation.rotate(rotateX, QVector3D(1, 0, 0));
        rotation.rotate(rotateY, QVector3D(0, 1, 0));

        ViewDir = DefaultViewDir * rotation;
        target = eye - ViewDir;
    }

    void CameraManager::UpdateViewMatrix() {
        QVector3D upDir(0, 1, 0);

        QVector3D N = eye - target;
        QVector3D U = QVector3D::crossProduct(upDir, N);
        QVector3D V = QVector3D::crossProduct(N, U);

        N.normalize();
        U.normalize();
        V.normalize();

        viewMatrix.setRow(0, {U.x(), U.y(), U.z(), -QVector3D::dotProduct(U, eye)}); // x
        viewMatrix.setRow(1, {V.x(), V.y(), V.z(), -QVector3D::dotProduct(V, eye)}); // y
        viewMatrix.setRow(2, {N.x(), N.y(), N.z(), -QVector3D::dotProduct(N, eye)}); // z
        viewMatrix.setRow(3, {0, 0, 0, 1});
    }

    void CameraManager::MoveStep(QVector3D &dir, QVector3D step) {
        dir.setX(dir.x() + step.x());
        dir.setZ(dir.z() + step.z());
    }

    void CameraManager::MoveLeft(float step) {
        QVector3D upDir(0, 1, 0);
        QVector3D U = QVector3D::crossProduct(upDir, ViewDir);
        MoveStep(target, -step * SENSITIVITY * U);
        MoveStep(eye, -step * SENSITIVITY * U);

        UpdateViewMatrix();
    }

    void CameraManager::MoveRight(float step) {
        QVector3D upDir(0, 1, 0);
        QVector3D U = QVector3D::crossProduct(upDir, ViewDir);

        MoveStep(target, step * SENSITIVITY  * U);
        MoveStep(eye, step * SENSITIVITY * U);

        UpdateViewMatrix();
    }

    void CameraManager::MoveFront(float step) {
        MoveStep(target, -step * SENSITIVITY * ViewDir);
        MoveStep(eye, -step * SENSITIVITY * ViewDir);

        UpdateViewMatrix();
    }

    void CameraManager::MoveBack(float step) {
        MoveStep(target, step * SENSITIVITY * ViewDir);
        MoveStep(eye, step * SENSITIVITY * ViewDir);

        UpdateViewMatrix();
    }

    void CameraManager::MoveUp(float step) {
        eye.setY(eye.y() + step* SENSITIVITY );
        target.setY(target.y() + step* SENSITIVITY );
        UpdateViewMatrix();
    }

    void CameraManager::MoveDown(float step) {
        eye.setY(eye.y() - step* SENSITIVITY );
        target.setY(target.y() - step* SENSITIVITY );
        UpdateViewMatrix();
    }

    void CameraManager::Zoom(float step) {
        target -= step * SENSITIVITY * ViewDir;
        eye -= step * SENSITIVITY * ViewDir;

        UpdateViewMatrix();
    }
}