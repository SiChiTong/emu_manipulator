#ROS2 import
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

#Our toolbox
from .com import Uart

class SerialTransmitter(Node):
    def __init__(self):
        super().__init__('serial_transmitter')
        self.serial_com = Uart('emulatorTX', '/dev/ttyTHS1', 1000000)
        
        self.subscription = self.create_subscription(String, 'emulatorTransmit', self.listener_callback, 10)
        self.subscription

    def listener_callback(self, msg):
        self.get_logger().info('Serial out: {}'.format(msg.data))
        self.serial_com.write_line(msg.data.encode())

def main(args=None):
    rclpy.init(args=args)

    serial_transmitter = SerialTransmitter()

    rclpy.spin(serial_transmitter)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    serial_transmitter.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
