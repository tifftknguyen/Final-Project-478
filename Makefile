
clean: 
	docker compose down --rmi all --volumes --remove-orphans
	
up:
	docker compose build --no-cache

demo:
	docker compose run --rm fsguardian

scan: # FOR THE PURPOSE OF TROUBLESHOOTING ONE TEST CASE FILE
	docker compose run --rm fsguardian ./fsguard $(t)

