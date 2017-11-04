require 'agens'

require_relative 'communication/I2C.rb'

require 'agens'

# Definition
class UltrasonicSensor < Sensor

end

class Motor < Actuator

end

class MovementAgent < Agent
	def setup
		sensor UltrasonicSensor
		actuator Motor
	end

	def perform_reasoning
		forward
	end
end

class ProbeeMAS < MAS
	agent MovementAgent
end


class Jessie < ExampleAgent

end

class ExampleMAS < MAS
	agent Jessie
	agent James
end

# Program
mas = ExampleMAS.new
mas.run

mas.world.dump

sleep(2)

mas.shutdown
