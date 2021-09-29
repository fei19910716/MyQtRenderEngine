#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include <QVector3D>
#include <QMatrix4x4>
namespace render {
    /**
     * https://blog.csdn.net/ZJU_fish1996/article/details/84726192
     */
    class CameraManager {
    private:
        QVector3D DefaultViewDir;
        QVector3D ViewDir = QVector3D(0, 0, 1);
        float rotateX = 0.0f;
        float rotateY = 0.0f;

        QVector3D eye = QVector3D(0, 1, 4);
        QVector3D target = QVector3D(0, 0, 0);
        QMatrix4x4 viewMatrix;

        void MoveStep(QVector3D &dir, QVector3D step);

        CameraManager();

    public:
        static CameraManager *camera;

        static CameraManager *Inst() {
            if (!camera) {
                camera = new CameraManager();
            }
            return camera;
        }

        void SetRotateXY(float x, float y);

        float GetRotateX() { return rotateX; }

        float GetRotateY() { return rotateY; }

        void MoveLeft(float step);

        void MoveRight(float step);

        void MoveFront(float step);

        void MoveBack(float step);

        void MoveUp(float step);

        void MoveDown(float step);

        void Zoom(float step);

        void UpdateViewMatrix();

        const QMatrix4x4 &GetViewMatrix() { return viewMatrix; }

        const QVector3D &GetCameraPos() { return eye; }

        const QVector3D &GetViewDir() { return ViewDir; }
    };
}
#endif // CAMERAMANAGER_H